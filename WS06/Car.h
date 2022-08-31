#ifndef SDDS_CAR_H
#define SDDS_CAR_H

#include <iostream>
#include "Vehicle.h"

namespace sdds
{
	class Car : public Vehicle
	{
		std::string m_maker{};
		std::string m_condition{};
		double m_topSpeed{ 0 };
		void trim(std::string& src);
	public:
		Car() {};
		Car(std::istream& in);
		Car(const Car& src);
		Car(Car&& src) noexcept;
		Car& operator=(const Car& src);
		Car& operator=(Car&& src) noexcept;
		~Car() {};

		std::string condition() const;
		double topSpeed() const;
		void display(std::ostream& out) const;
	};
}


#endif // !SDDS_CAR_H

