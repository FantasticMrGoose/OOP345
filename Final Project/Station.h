#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Utilities.h"

namespace sdds
{
	class Station
	{
		int m_stationID{ 0 };
		std::string m_item{};
		std::string m_desc{};
		size_t m_serial{ 0 };
		size_t m_stock{ 0 };
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station() {};
		Station(const std::string& in);

		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H
