#include "Autoshop.h"

namespace sdds
{
	Autoshop& Autoshop::operator+=(Vehicle* theVehicle)
	{
		this->m_vehicles.push_back(theVehicle);
		return *this;
	}

	void Autoshop::display(std::ostream& out) const
	{
		out << "--------------------------------" << std::endl;
		out << "| Cars in the autoshop!        |" << std::endl;
		out << "--------------------------------" << std::endl;
		for (auto iter = m_vehicles.begin(); iter != m_vehicles.end(); iter++)
		{
			(*iter)->display(out);
			out << std::endl;
		}
		out << "--------------------------------" << std::endl;
	}

	Autoshop::~Autoshop()
	{
		for (auto &veh : m_vehicles) {
			delete veh;
		}
	}
}