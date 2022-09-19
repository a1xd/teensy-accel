struct settings {
    int dpi = 1800; // set to 0 to ignore normalization to 1000 dpi
    
    double domain_weight = 0.8;
    double range_weight = 0.2;
    double sens_multiplier = 0.7;
    double yx_sens_ratio = 1.2;
};

inline double accel_factor(double x)
{
  if (x <= 1) 
      return 1;
      
  return log(x) + 1 / x;
}

struct vec2d { double x, y; };

using milliseconds = double;

constexpr 
class modifier {
public:
    constexpr modifier(const settings& args) :
        domain_weight{args.domain_weight * ((args.dpi > 0) ? (1e3 / args.dpi) : 1)},
        range_weight{args.range_weight},
        sens_x{args.sens_multiplier / args.domain_weight},
        sens_y{sens_x * args.yx_sens_ratio} {}
	
    void modify(vec2d& in, milliseconds t) const
    {
        in.x *= domain_weight;
        in.y *= domain_weight;

        double speed = sqrt(in.x * in.x + in.y * in.y) / t;
        
        double scale = 1 + range_weight * (accel_factor(speed) - 1);
        in.x *= scale;
        in.y *= scale;

        in.x *= sens_x;
        in.y *= sens_y;
    }

private:
    double domain_weight;
    double range_weight;
    double sens_x;
    double sens_y;
} mod{settings{}};
