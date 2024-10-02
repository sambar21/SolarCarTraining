#ifndef MINISIM_VECTOR_H
#define MINISIM_VECTOR_H

#include <cmath>

struct VelocityVector {
public:
    static VelocityVector from_cartesian_components(double north_south, double east_west);
    static VelocityVector from_polar_components(double speed, double heading);

    double get_north_south() const;
    double get_east_west() const;
    double get_magnitude() const;
    double get_heading() const;
    double angle_between(const VelocityVector& other) const;

private:
    double north_south;
    double east_west;

    VelocityVector(double north_south, double east_west);
};

struct ApparentWindVector {
    double speed;
    double yaw;
};

#endif  // MINISIM_VECTOR_H
