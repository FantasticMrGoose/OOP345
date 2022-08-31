#include <sstream>
#include "Utilities.h"

namespace sdds
{
	Vehicle* createInstance(std::istream& in)
	{
		Car* car{};
		Racecar* racecar{};
		std::stringstream ssobj;
		std::string temp;

		std::getline(in, temp);
		if (!temp.empty())
		{
			size_t begin = temp.find_first_not_of(' ');
			size_t end = temp.find_last_not_of(' ');
			temp = temp.substr(begin, (end - begin + 1));

			if (temp.at(0) == 'c' || temp.at(0) == 'C')
			{				
				temp = temp.substr(temp.find(",") + 1, temp.length());
				ssobj << temp;
				car = new Car(ssobj); //passes the sstream to Car
				return car;
			}
			else if (temp.at(0) == 'r' || temp.at(0) == 'R') 
			{
				temp = temp.substr(temp.find(",") + 1, temp.length());
				ssobj << temp;
				racecar = new Racecar(ssobj);
				return racecar;
			}
			else
			{
				temp = temp.substr(0, temp.find(","));
				std::string error = ("Unrecognized record type: [") + temp + "]";
				throw error;
			}
		}
		return nullptr;
	}
}