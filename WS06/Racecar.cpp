#include "Racecar.h"

namespace sdds
{
	Racecar::Racecar(std::istream& in) : Car(in)
	{
		std::string temp;
		getline(in, temp);
		m_booster = stod(temp);
	}

	void Racecar::display(std::ostream& out) const
	{
		Car::display(out);
		out << "*";
	}
	double Racecar::topSpeed() const
	{
		return (Car::topSpeed() * (1 + m_booster));
	}
}