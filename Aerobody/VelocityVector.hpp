#ifndef MINISIM_VECTOR_H
#define MINISIM_VECTOR_H

#include <cmath>
#include <numbers>  // 2π = std::numbers::pi * 2

struct VelocityVector {
   public:
	/// @brief constructs a velocity vector using it's components
	///
	/// @param north_sourth (m/s) the North-South component of the wind vector
	/// @param east_west (m/s) the East-West component of the wind vector
	static VelocityVector from_cartesian_components(double north_south, double east_west) {
		return VelocityVector(north_south, east_west);
	}

	/// @brief constructs a velocity vector using polar form
	///
	/// @param speed (m/s) the magnitude of the velocity vector
	/// @param the (radians) direction of the velocity vector. Note 0 radians is due north, π/4
	/// radians is due east
	static VelocityVector from_polar_components(double speed, double heading) {
		return VelocityVector(          //
			speed * std::cos(heading),  // north_south
			speed * std::sin(heading)   // east_west
		);
	}

	double get_north_south() const {
		return north_south;
	}

	double get_east_west() const {
		return east_west;
	}

	/// @brief Calculate the magnitude of the vector
	double get_magnitude() const {
		/// TODO: Return Something Meaningful
		
		return std::hypot(east_west, north_south);
		
	}

	/// @brief Calculates the heading
	/// @note recall that 0 radians is due north, and π/2 radians is due east, and the range is
	/// [0, 2π]
	double get_heading(double north_south, double east_west) {
    double pi = std::numbers::pi;
    double range = std::atan2(north_south, east_west);

    if (range < 0) {
        range += 2 * pi;  
    }

    return range;
}



	/// @brief Calculate the angle, in radians, between the two vectors
	///
	/// @return (radians) the angle between two vectors
	/// @note positive if { other } is "left" of this vector
	/// @note zero if either vector is 0
	/// @hint you might need to use the dot product
	double angle_between(const VelocityVector& other) const {
		// TODO: Return Something Meaningful
		if(this-> get_magnitude()==0 || other.get_magnitude()==0){
			return 0;
		}
		const double dot_product = north_south*other.north_south + east_west*other.east_west;
		const double cross_product = north_south*other.east_west - other.north_south*east_west;
		return atan2(cross_product, dot_product);
		
	}

   private:
	/// @brief (m/s) North-South component of wind vector
	double north_south;

	/// @brief (m/s) East-West component of wind vector
	double east_west;

	VelocityVector(double north_south, double east_west)
		: north_south(north_south), east_west(east_west) {}
};

/// @brief An apparent wind vector in its traditional polar coordinates
struct ApparentWindVector {
	/// @brief (m/s) Speed of wind vector
	double speed;

	/// @brief (m/s) Yaw of wind vector in radians from heading
	///
	/// @note positive yaw is starboard
	double yaw;
};

#endif  // MINISIM_VECTOR_H