#pragma once

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "Utilities.h"
#include "Workstation.h"

namespace sdds
{
	class LineManager
	{
		std::vector<Workstation*> activeLine{};
		size_t m_cntCustomerOrder = 0;
		Workstation* m_firstStation = nullptr;
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);

		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}


