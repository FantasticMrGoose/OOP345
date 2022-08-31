#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>
#include "Vehicle.h"
#include "Car.h"
#include "Racecar.h"

namespace sdds
{
	Vehicle* createInstance(std::istream& in);
}

#endif // !SDDS_UTILITIES





