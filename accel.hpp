#include "rawaccel-common/rawaccel.hpp"

using namespace rawaccel;

// optional, for normalization to 1000 dpi
constexpr int dpi = 0;

const profile profile_settings = []{
    profile args;
    
    /*
    Mode definitions 
    
    enum class accel_mode {
        classic,
        jump,
        natural,
        motivity,
        power,
        lookup,
        noaccel
    };

    enum class cap_mode_t {
        io, 
        in, 
        out
    };
    */

    args.whole = true;
    args.lp_norm = 2;
    args.domain_weights = { 1, 1 };
    args.range_weights = { 1, 1 };
    
    args.sensitivity = 1;
    args.yx_sens_ratio = 1;
    args.lr_sens_ratio = 1;
    args.ud_sens_ratio = 1;

    args.degrees_rotation = 0;

    args.degrees_snap = 0;

    args.speed_min = 0;
    args.speed_max = 0;
    
    
    //
    // Whole or X accel parameters
    //
    args.accel_x.mode = accel_mode::noaccel;
    args.accel_x.gain = 1;

    args.accel_x.input_offset = 0;
    args.accel_x.output_offset = 0;
    args.accel_x.acceleration = 0.005;
    args.accel_x.decay_rate = 0.1;
    args.accel_x.growth_rate = 1;
    args.accel_x.motivity = 1.5;
    args.accel_x.exponent_classic = 2;
    args.accel_x.scale = 1;
    args.accel_x.exponent_power = 0.05;
    args.accel_x.limit = 1.5;
    args.accel_x.midpoint = 5;
    args.accel_x.smooth = 0.5;

    args.accel_x.cap = { 15, 1.5 };
    args.accel_x.cap_mode = cap_mode_t::out;
        
    
    //
    // Y accel parameters
    //
    args.accel_y.mode = accel_mode::noaccel;
    args.accel_y.gain = 1;

    args.accel_y.input_offset = 0;
    args.accel_y.output_offset = 0;
    args.accel_y.acceleration = 0.005;
    args.accel_y.decay_rate = 0.1;
    args.accel_y.growth_rate = 1;
    args.accel_y.motivity = 1.5;
    args.accel_y.exponent_classic = 2;
    args.accel_y.scale = 1;
    args.accel_y.exponent_power = 0.05;
    args.accel_y.limit = 1.5;
    args.accel_y.midpoint = 5;
    args.accel_y.smooth = 0.5;

    args.accel_y.cap = { 15, 1.5 };
    args.accel_y.cap_mode = cap_mode_t::out;

    return args;
}();

const struct ra_mod_pair {
    modifier_settings settings;
    modifier mod;
} mod_pair = []{
    ra_mod_pair ret;
    ret.settings = { profile_settings };
    init_data(ret.settings);
    ret.mod = { ret.settings };
    return ret;
}();
