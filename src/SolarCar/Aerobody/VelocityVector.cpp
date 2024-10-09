#include "VelocityVector.h"
#include <numbers>  // for π = std::numbers::pi
#include <cmath>


VelocityVector VelocityVector::from_cartesian_components(double north_south, double east_west) {
    return VelocityVector(north_south, east_west);
}

VelocityVector VelocityVector::from_polar_components(double speed, double heading) {
    return VelocityVector(          //
        speed * std::cos(heading),  // north_south
        speed * std::sin(heading)   // east_west
    );
}

double VelocityVector::get_north_south() const {
    return north_south;
}

double VelocityVector::get_east_west() const {
    return east_west;
}

double VelocityVector::get_magnitude() const {
    return std::hypot(east_west, north_south);
}

double VelocityVector::get_heading() const {
    double pi = std::numbers::pi;
    double range = std::atan2(east_west, north_south);

    if (range < 0) {
        range += 2 * pi;
    }

    return range;
}

double VelocityVector::angle_between(const VelocityVector& other) const {
    if (this->get_magnitude() == 0 || other.get_magnitude() == 0) {
        return 0;
    }
    const double dot_product = north_south * other.north_south + east_west * other.east_west;
    const double cross_product = north_south * other.east_west - other.north_south * east_west;
    return -atan2(cross_product, dot_product);
}

VelocityVector::VelocityVector(double north_south, double east_west)
    : north_south(north_south), east_west(east_west) {}
