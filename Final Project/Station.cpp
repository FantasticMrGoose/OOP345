#include "Station.h"

namespace sdds
{
	// initialize two static variables
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& in)
	{
		Utilities utl; 

		size_t pos = 0;
		bool more = false;
		m_stationID = ++Station::id_generator;

		try
		{
			m_item = utl.extractToken(in, pos, more);

			// convert string to size_t
			std::stringstream serial(utl.extractToken(in, pos, more));
			serial >> m_serial;
			std::stringstream stock(utl.extractToken(in, pos, more));
			stock >> m_stock;

			Station::m_widthField = std::max(utl.getFieldWidth(), Station::m_widthField);
			m_desc = utl.extractToken(in, pos, more);
		}
		catch (const std::string error)
		{
			std::cout << error << std::endl;
		}
	}

	const std::string& Station::getItemName() const
	{
		return m_item;
	}

	size_t Station::getNextSerialNumber()
	{
		m_serial++;
		return m_serial - 1;
	}

	size_t Station::getQuantity() const
	{
		return m_stock;
	}

	void Station::updateQuantity()
	{
		if (m_stock > 0)
		{
			m_stock -= 1;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << "[" << std::right << std::setw(3) << std::setfill('0') << m_stationID
			<< "] Item: " << std::left << std::setw(Station::m_widthField)
			<< std::setfill(' ') << m_item << " [" << std::right 
			<< std::setw(6) << std::setfill('0') << m_serial << "]";
		if (!full)
		{
			os << std::endl;
		}
		else
		{
			os << " Quantity: " << std::setw(Station::m_widthField)
				<< std::setfill(' ') <<std::left << m_stock << " Description: " << m_desc << std::endl;
		}
	}
}