#include "Array.h"
double Array::power_in(double irradiance) const{

double array_effeciency_fraction = array_efficiency/100.0;
return (irradiance * array_area * array_effeciency_fraction);


}
