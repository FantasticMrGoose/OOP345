#include "LineManager.h"

namespace sdds
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		Utilities utl;
		std::string temp;

		std::ifstream assemble_file(file);
		if (!assemble_file)
		{
			std::string err = "ERROR: Cannot open file [" + file + "]";
			throw err;
		}
		
		while (!assemble_file.eof())
		{
			std::getline(assemble_file, temp);
			try
			{	
				Workstation* temp_workstation;
				Workstation* next_station;
				size_t pos = 0;
				bool more = true;

				// extract the string of the two stations (if exists)
				std::string file_item = utl.extractToken(temp, pos, more);
				std::string next_file_item;
				if (more)
				{
					next_file_item = utl.extractToken(temp, pos, more);
				}
				
				// find the station that matches the station in the file
				std::for_each(stations.begin(), stations.end(), 
					[&](Workstation* stations) {
						if (stations->getItemName() == file_item)
						{
							//store first station in temp pointer
							temp_workstation = stations;
						}
					});
				if (!next_file_item.empty())
				{
					std::for_each(stations.begin(), stations.end(),
						[&](Workstation* stations) {
							if (stations->getItemName() == next_file_item)
							{
								// store next station in another temp pointer
								next_station = stations;
							}
						});
					temp_workstation->setNextStation(next_station);
				}
				//push the temp workstation to the activeLine
				activeLine.push_back(temp_workstation);
			}
			catch (const std::string error)
			{
				std::cout << error << std::endl;
			}	
		}

		//finds the first station regardless of the order of AssemblyLine.txt
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* first_line) {

			// find the activeLine where it's station does not show up in the next station
			// if that station is not in any nextStation, it is the first station
			bool found = false;
			found = std::none_of(activeLine.begin(), activeLine.end(), [&](const Workstation* activeLine)
				{
					bool match = false;
					if (activeLine->getNextStation() != nullptr) {
						// if the activeLine's next station item is the same as the first_line's item, 
						//then it is not the first station.
						if (first_line->getItemName() == activeLine->getNextStation()->getItemName())
							match = true;
					}
					return match;
				});

			if (found)
			{
				m_firstStation = first_line;
			} 
			});
		m_cntCustomerOrder = pending.size();
	}
	

	void LineManager::linkStations()
	{
		std::vector<Workstation*> temp_line{};
		temp_line.push_back(m_firstStation);

		while (temp_line.back()->getNextStation())
		{
			temp_line.push_back(temp_line.back()->getNextStation());
		}
		activeLine = temp_line;
	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t iter = 1;

		os << "Line Manager Iteration: " << iter++ << std::endl;
		if (!pending.empty())
		{
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}
		// fill and move order in activeLine
		std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* activeLine) {
			activeLine->fill(os);});

		std::for_each(activeLine.begin(), activeLine.end(), [](Workstation* activeLine) {
			activeLine->attemptToMoveOrder();
			});

		return m_cntCustomerOrder == completed.size() + incomplete.size();
	}

	void LineManager::display(std::ostream& os) const
	{
		std::for_each(activeLine.begin(), activeLine.end(), [&os](const Workstation* activeLine) {
			activeLine->display(os);
			});
	}
}