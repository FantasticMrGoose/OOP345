#ifndef SDDS_AUTOSHOP_H
#define SDDS_AUTOSHOP_H

#include <vector>
#include <list>
#include "Vehicle.h"


namespace sdds
{
	class Autoshop
	{
		std::vector<Vehicle*> m_vehicles; //empty container
	public:
		Autoshop& operator +=(Vehicle* theVehicle);
		void display(std::ostream& out) const;
		~Autoshop();

		template<typename T>
		void select(T test, std::list<const Vehicle*>& vehicles) {
			for (auto &veh : m_vehicles) {
				if (test(veh))
				{
					vehicles.push_back(veh);
				}
			}
		}

	};
}

#endif // !SDDS_AUTOSHOP_H


