#include "Motor.h"
#include <cmath>

/// @brief Calculates the power the motor consumed to rotate at
	//// @p angular_speed with @p torque.
	///
	/// @param angular_speed (rad/s) the angular speed the motor is rotating at.
	/// @param torque (Nm) the torque that the motor is operating with.
	///
	/// @note negative torque means regenerative braking.
	double Motor::power_consumed(double angular_speed, double torque) const{

        return((eddy_current_loss_coefficient * angular_speed) + hysteresis_loss) + (angular_speed * torque);



    }

