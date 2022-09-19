#pragma once

#include "rawaccel-base.hpp"
#include "utility.hpp"

namespace rawaccel {

	struct valid_profile_ret_t {
		int last_x = 0;
		int last_y = 0;
		int count = 0;

		explicit operator bool() const
		{
			return count == 0;
		}
	};

	struct valid_device_ret_t {
		int count = 0;

		explicit operator bool() const
		{
			return count == 0;
		}
	};

	template <typename MsgHandler = noop>
	valid_profile_ret_t valid(const profile& args, MsgHandler fn = {})
	{
		valid_profile_ret_t ret;

		auto error = [&](auto msg) {
			++ret.count;
			fn(msg);
		};

		auto check_accel = [&error](const accel_args& args) {
			static_assert(LUT_POINTS_CAPACITY == 257, "update error msg");

			if (args.mode == accel_mode::lookup) {
				if (args.length < 4) {
					error("lookup mode requires at least 2 points");
				}
				else if (args.length > ra::LUT_RAW_DATA_CAPACITY) {
					error("too many data points (max=257)");
				}
			}
			else if (args.length > ra::LUT_RAW_DATA_CAPACITY) {
				error("data size > max");
			}

			if (args.input_offset < 0) {
				error("offset can not be negative");
			}

			if (args.output_offset < 0) {
				error("offset can not be negative");
			}

			bool jump_or_io_cap = 
				(args.mode == accel_mode::jump || 
					((args.mode == accel_mode::classic || args.mode == accel_mode::power) &&
						args.cap_mode == cap_mode::io));

			if (args.cap.x < 0) {
				error("cap (input) can not be negative");
			}
			else if (args.cap.x == 0 && jump_or_io_cap) {
				error("cap (input) can not be 0");
			}

			if (args.cap.y < 0) {
				error("cap (output) can not be negative");
			}
			else if (args.cap.y == 0 && jump_or_io_cap) {
				error("cap (output) can not be 0");
			}

			if ((args.mode == accel_mode::classic && 
					args.cap.x > 0 && 
					args.cap.x < args.input_offset && 
					args.cap_mode != cap_mode::out) ||
				(args.mode == accel_mode::power &&
					args.cap.y > 0 &&
					args.cap.y < args.output_offset &&
					args.cap_mode != cap_mode::in)) {
				error("cap < offset");
			}

			if (args.acceleration <= 0) {
				error("acceleration"" must be positive");
			}

			if (args.scale <= 0) {
				error("scale"" must be positive");
			}

			if (args.growth_rate <= 0) {
				error("growth rate"" must be positive");
			}

			if (args.decay_rate <= 0) {
				error("decay rate"" must be positive");
			}

			if (args.motivity <= 1) {
				error("motivity must be greater than 1");
			}

			if (args.exponent_classic <= 1) {
				error("exponent must be greater than 1");
			}

			if (args.exponent_power <= 0) {
				error("exponent"" must be positive");
			}

			if (args.limit <= 0) {
				error("limit"" must be positive");
			}

			if (args.midpoint <= 0) {
				error("midpoint"" must be positive");
			}

			if (args.smooth < 0 || args.smooth > 1) {
				error("smooth must be between 0 and 1");
			}

		};

		check_accel(args.accel_x);

		if (!args.whole) {
			ret.last_x = ret.count;
			check_accel(args.accel_y);
			ret.last_y = ret.count;
		}

		if (args.name[0] == L'\0') {
			error("profile name can not be empty");
		}

		if (args.speed_max < 0) {
			error("speed cap is negative");
		}
		else if (args.speed_max < args.speed_min) {
			error("max speed is less than min speed");
		}

		if (args.degrees_snap < 0 || args.degrees_snap > 45) {
			error("snap angle must be between 0 and 45 degrees");
		}

		if (args.sensitivity == 0) {
			error("sens multiplier is 0");
		}
	
		if (args.yx_sens_ratio == 0) {
			error("Y/X sens ratio is 0");
		}

		if (args.domain_weights.x <= 0 ||
			args.domain_weights.y <= 0) {
			error("domain weights"" must be positive");
		}

		if (args.lr_sens_ratio <= 0 || args.ud_sens_ratio <= 0) {
			error("sens ratio must be positive");
		}

		if (args.lp_norm <= 0) {
			error("Lp norm must be positive (default=2)");
		}

		if (args.range_weights.x < 0 || args.range_weights.y < 0) {
			error("range weights"" must be positive");
		}

		return ret;
	}

	template <typename MsgHandler = noop>
	valid_device_ret_t valid(const device_settings& args, MsgHandler fn = {})
	{
		valid_device_ret_t ret;

		auto error = [&](auto msg) {
			++ret.count;
			fn(msg);
		};


		if (args.config.dpi < 0) {
			error("dpi"" can not be negative");
		}

		if (args.config.polling_rate < 0) {
			error("polling rate"" can not be negative");
		}

		if (args.config.clamp.min <= 0) {
			error("minimum time"" must be positive");
		}

		if (args.config.clamp.max < args.config.clamp.min) {
			error("max time is less than min time");
		}

		return ret;
	}
}
