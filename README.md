### Teensy Accel

This turns the Teensy 4.1 development board into a usb->usb filter with mouse acceleration. 

#### Hardware
Besides a [Teensy 4.1 board](https://www.pjrc.com/store/teensy41.html) and a micro USB cable, you'll need to get, and solder, [5 header pins](https://www.pjrc.com/store/header_14x1.html) for the [USB host cable](https://www.pjrc.com/store/cable_usb_host_t36.html).

#### Installation 
- Follow the [Teensyduino installation guide](https://www.pjrc.com/teensy/td_download.html) 
	> **Note**
	> Teensyduino (as of v1.57) is only compatible with the legacy Arduino IDE (v1.8.19)
- Open *teensy-accel.ino* in the Arduino IDE 
- Edit the Raw Accel `profile_settings` definition in *accel.hpp*
- In the IDE *Tools* menu, ensure "Teensy 4.1" and "Keyboard + Mouse + Joystick" are selected under *Board* and *USB Type*
- Plug in the board and click 'Upload'

#### Limitations
- Input device is expected to request 1000hz polling rate
- Output movement values are represented by 1 byte (max counts = 127); inputs from faster motions could get clamped, depending on settings and dpi