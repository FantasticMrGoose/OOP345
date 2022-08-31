#include <iomanip>
#include "Car.h"

namespace sdds
{
	void Car::trim(std::string& src)
	{
		if (!src.empty() && src.length() > 1)
		{
			size_t begin = src.find_first_not_of(' ');
			size_t end = src.find_last_not_of(' ');
			src = src.substr(begin, (end - begin + 1));
		}
	}

	Car::Car(std::istream& in)
	{
		std::string temp;
		std::getline(in, temp, ','); // gets the first field


		m_maker = temp;
		trim(m_maker);

		std::getline(in, temp, ','); // gets the second field
		trim(temp);
		
		if (temp.empty() || temp.at(0) == 'n')
		{
			m_condition = "new";
		}
		else if (temp == " ")
		{
			m_condition = "new";
		}
		else if (temp.at(0) == 'u')
		{
			m_condition = "used";
		}
		else if (temp.at(0) == 'b')
		{
			m_condition = "broken";
		}
		else if (temp.at(0) != 'n' || temp.at(0) != 'u' || temp.at(0) != 'b')
		{
			std::string error = "Invalid record!";
			throw error;
		}

		std::getline(in, temp, ','); // gets the third field
		try
		{
			m_topSpeed = std::stod(temp);
		}
		catch (std::invalid_argument const& e)
		{
			std::string err = "Invalid record!";
			throw err;
		}
	}

	Car::Car(const Car& src)
	{
		*this = src;
	}

	Car::Car(Car&& src) noexcept
	{
		*this = std::move(src);
	}

	Car& Car::operator=(const Car& src)
	{
		if (this != &src)
		{
			this->m_maker = src.m_maker;
			this->m_condition = src.m_condition;
			this->m_topSpeed = src.m_topSpeed;
		}
		return *this;
	}

	Car& Car::operator=(Car&& src) noexcept
	{
		if (this != &src)
		{
			this->m_maker = src.m_maker;
			this->m_condition = src.m_condition;
			this->m_topSpeed = src.m_topSpeed;

			src.m_maker.clear();
			src.m_condition.clear();
			src.m_topSpeed = 0u;
		}
		return *this;
	}

	std::string Car::condition() const
	{
		return m_condition;
	}

	double Car::topSpeed() const
	{
		return m_topSpeed;
	}

	void Car::display(std::ostream& out) const
	{
		out << "| " << std::setw(10) << std::right << m_maker << " | "
			<< std::setw(6) << std::left << condition() << " | "
			<< std::setw(6) << std::fixed << std::setprecision(2) << topSpeed() << " |";
	}
}

