#include <iostream>
#include <iomanip>
#include "Reservation.h"

namespace sdds
{
	Reservation::Reservation(const std::string& res)
	{
		std::string temp_res = res;

		m_id = temp_res.substr(0, temp_res.find(":"));
		//removes the part of string that has already been assigned to class
		temp_res = temp_res.substr(temp_res.find(":") + 1, temp_res.length());
		// removes leading and trailing whitespace from strings
		trim(m_id); 

		m_name = temp_res.substr(0, temp_res.find(","));
		temp_res = temp_res.substr(temp_res.find(",") + 1, temp_res.length());
		trim(m_name);

		m_email = temp_res.substr(0, temp_res.find(","));
		temp_res = temp_res.substr(temp_res.find(",") + 1, temp_res.length());
		trim(m_email);

		m_numPeople = std::stoi(temp_res.substr(0, temp_res.find(",")));
		temp_res = temp_res.substr(temp_res.find(",") + 1, temp_res.length());

		m_partyDay = std::stoi(temp_res.substr(0, temp_res.find(",")));
		temp_res = temp_res.substr(temp_res.find(",") + 1, temp_res.length());

		m_partyHour = std::stoi(temp_res.substr(0, temp_res.find(",")));

	}

	Reservation::Reservation(const Reservation& src)
	{
		*this = src;
	}

	Reservation& Reservation::operator=(const Reservation& src)
	{
		if (this != &src)
		{
			this->m_id = src.m_id;
			this->m_name = src.m_name;
			this->m_email = src.m_email;
			this->m_numPeople = src.m_numPeople;
			this->m_partyDay = src.m_partyDay;
			this->m_partyHour = src.m_partyHour;
		}
		return *this;
	}

	Reservation::Reservation(Reservation&& src) noexcept
	{
		*this = std::move(src);
	}

	Reservation& Reservation::operator=(Reservation&& src) noexcept
	{
		this->m_id = src.m_id;
		this->m_name = src.m_name;
		this->m_email = src.m_email;
		this->m_numPeople = src.m_numPeople;
		this->m_partyDay = src.m_partyDay;
		this->m_partyHour = src.m_partyHour;

		src.m_id.clear();
		src.m_name.clear();
		src.m_email.clear();
		src.m_numPeople = 0;
		src.m_partyDay = 0;
		src.m_partyHour = 0;
		return *this;
	}

	void Reservation::update(int day, int time)
	{
		m_partyDay = day;
		m_partyHour = time;
	}

	void Reservation::trim(std::string& src)
	{
		size_t begin = src.find_first_not_of(' ');
		size_t end = src.find_last_not_of(' ');
		src = src.substr(begin, (end - begin + 1));
	}                     

	std::ostream& operator<<(std::ostream& os, const Reservation& res)
	{
		if (res.m_partyHour >= 6 && res.m_partyHour <= 9)
		{
			os << "Reservation " << std::setw(10) << std::right << res.m_id << ": "
				<< std::setw(20) << res.m_name << "  " << std::setw(20) << std::left << "<" + res.m_email + ">" << "    Breakfast on day "
				<< res.m_partyDay << " @ " << res.m_partyHour << ":00 for "
				<< res.m_numPeople;
			if (res.m_numPeople > 1)
			{
				os << " people." << std::endl;
			} 
			else
			{
				os << " person." << std::endl;
			}
		}
		else if (res.m_partyHour >= 11 && res.m_partyHour <= 15)
		{
			os << "Reservation " << std::setw(10) << std::right << res.m_id << ": "
				<< std::setw(20) << res.m_name << "  " << std::setw(20) << std::left << "<" + res.m_email + ">" << "    Lunch on day "
				<< res.m_partyDay << " @ " << res.m_partyHour << ":00 for "
				<< res.m_numPeople;
			if (res.m_numPeople > 1)
			{
				os << " people." << std::endl;
			}
			else
			{
				os << " person." << std::endl;
			}
			
		}
		else if (res.m_partyHour >= 17 && res.m_partyHour <= 21)
		{
			os << "Reservation " << std::setw(10) << std::right << res.m_id << ": "
				<< std::setw(20) << res.m_name << "  " << std::setw(20) << std::left << "<" + res.m_email + ">" << "    Dinner on day "
				<< res.m_partyDay << " @ " << res.m_partyHour << ":00 for "
				<< res.m_numPeople;
			if (res.m_numPeople > 1)
			{
				os << " people." << std::endl;
			}
			else
			{
				os << " person." << std::endl;
			}
			
		}
		else
		{
			os << "Reservation " << std::setw(10) << std::right << res.m_id << ": "
				<< std::setw(20) << res.m_name << "  " << std::setw(20) << std::left << "<" + res.m_email + ">" << "    Drinks on day "
				<< res.m_partyDay << " @ " << res.m_partyHour << ":00 for "
				<< res.m_numPeople;
			if (res.m_numPeople > 1)
			{
				os << " people." << std::endl;
			}
			else
			{
				os << " person." << std::endl;
			}
		}
		return os;
	}
}