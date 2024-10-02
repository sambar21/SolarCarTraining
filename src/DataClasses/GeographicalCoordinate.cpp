#include "GeographicalCoordinate.h"

// overload addition operator for GeographicalCoordinate
GeographicalCoordinate operator+(const GeographicalCoordinate& lhs, const GeographicalCoordinate& rhs) {
	return {lhs.latitude + rhs.latitude, lhs.longitude + rhs.longitude};
}

// overload subtraction operator for GeographicalCoordinate
GeographicalCoordinate operator-(const GeographicalCoordinate& lhs, const GeographicalCoordinate& rhs) {
	return {lhs.latitude - rhs.latitude, lhs.longitude - rhs.longitude};
}

// overload multiplication operator for GeographicalCoordinate
GeographicalCoordinate operator*(const GeographicalCoordinate& lhs, double rhs) {
	return {lhs.latitude * rhs, lhs.longitude * rhs};
}

// overload multiplication operator for GeographicalCoordinate
GeographicalCoordinate operator*(double& lhs, const GeographicalCoordinate& rhs) {
	return {lhs * rhs.latitude, lhs * rhs.longitude};
}

// overload division operator for GeographicalCoordinate
GeographicalCoordinate operator/(const GeographicalCoordinate& lhs, double rhs) {
	return {lhs.latitude / rhs, lhs.longitude / rhs};
}

// Average two GeographicalCoordinates
GeographicalCoordinate GeographicalCoordinate::average(
	const GeographicalCoordinate& lhs, const GeographicalCoordinate& rhs) {
	return (lhs + rhs) / 2;
}
