#include <iomanip>
#include "Restaurant.h"

namespace sdds
{
	Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : m_numRes{ cnt }, m_reserve{ nullptr }
	{
		m_reserve = new Reservation[m_numRes];
		for (size_t i = 0; i < m_numRes; i++)
		{
			m_reserve[i] = *reservations[i];
		}
	}

	Restaurant::Restaurant(const Restaurant& src)
	{
		*this = src;
	}

	Restaurant& Restaurant::operator=(const Restaurant& src)
	{
		if (this != &src)
		{
			this->m_numRes = src.m_numRes;
			
			delete[] this->m_reserve;
			this->m_reserve = nullptr;
			if (src.m_reserve)
			{
				this->m_reserve = new Reservation[this->m_numRes];
				for (size_t i = 0; i < this->m_numRes; i++)
				{
					this->m_reserve[i] = src.m_reserve[i];
				}
			}
		}
		return *this;
	}

	Restaurant::Restaurant(Restaurant&& src) noexcept
	{
		*this = std::move(src);
	}

	Restaurant& Restaurant::operator=(Restaurant&& src) noexcept
	{
		if (this != &src)
		{
			delete[] this->m_reserve;
			this->m_reserve = src.m_reserve;
			src.m_reserve = nullptr;

			this->m_numRes = src.m_numRes;
			src.m_numRes = 0;
		}

		return *this;
	}

	size_t Restaurant::size() const
	{
		return m_numRes;
	}
	Restaurant::~Restaurant()
	{
		delete[] m_reserve;
	}

	std::ostream& operator<<(std::ostream& os, const Restaurant& res)
	{
		static size_t cnt{ 0 };
		cnt++;
		os << "--------------------------" << std::endl;
		os << "Fancy Restaurant (" << cnt << ")" << std::endl;
		os << "--------------------------" << std::endl;
		if (res.size() > 0)
		{
			for (size_t i = 0; i < res.size(); i++)
			{
				os << res.m_reserve[i];
			}
			os << "--------------------------" << std::endl;
		}
		else
		{
			os << "This restaurant is empty!" << std::endl;
			os << "--------------------------" << std::endl;
		}
		return os;
	}
}