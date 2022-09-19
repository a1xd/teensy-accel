#include "accel.hpp"

#include <USBHost_t36.h>

USBHost myusb;
USBHIDParser hid1(myusb);
MouseController mouse1(myusb);

unsigned long counter_us;
vec2d carry;

void setup() {
    myusb.begin();
}

void loop() {
    myusb.Task();

    if (mouse1.available()) {
        int x = mouse1.getMouseX();
        int y = mouse1.getMouseY();
        
        if (x || y) {
            auto now = micros();
            double elapsed_ms = [diff = now - counter_us]{
                return (diff ? diff : ~0ul) / 1e3;
            }();
            counter_us = now;

            vec2d in{ static_cast<double>(x), static_cast<double>(y) };
            
            mod_pair.mod.modify(in, mod_pair.settings, (dpi > 0) ? 1e3 / dpi : 1, elapsed_ms);

            in.x += carry.x;
            in.y += carry.y;
						
            x = static_cast<int>(in.x);
            y = static_cast<int>(in.y);

            carry.x = in.x - x;
            carry.y = in.y - y;
        }
        
        usb_mouse_buttons_state = mouse1.getButtons();
        Mouse.move(x, y, mouse1.getWheel(), mouse1.getWheelH());
        mouse1.mouseDataClear();
    }
}
