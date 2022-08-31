#include <iostream>
#include "ConfirmationSender.h"


namespace sdds
{
	ConfirmationSender::ConfirmationSender(const ConfirmationSender& src)
	{
		*this = src;
	}

	ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& src)
	{
		if (this != &src)
		{
			delete[] this->m_reserve;
			this->m_reserve = nullptr;
			
			this->m_count = src.m_count;

			if (src.m_reserve)
			{
				this->m_reserve = new const Reservation*[this->m_count];
				for (size_t i = 0; i < this->m_count; i++)
				{
					this->m_reserve[i] = src.m_reserve[i];
				}
			}
		}
		return *this;
	}

	ConfirmationSender::ConfirmationSender(ConfirmationSender&& src) noexcept
	{
		*this = std::move(src);
	}

	ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& src) noexcept
	{
		if (this != &src)
		{
			delete[] this->m_reserve;
			this->m_reserve = src.m_reserve;
			src.m_reserve = nullptr;

			this->m_count = src.m_count;
			src.m_count = 0;
		}
		return *this;
	}

	ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res)
	{
		bool same = false;

		// check if reservation is already in array
		for (size_t i = 0; i < m_count && !same; i++) {
			if (m_reserve[i] == &res)
			{
				same = true;
			}
		}

		if (!same) //skip if res in array
		{
			const sdds::Reservation** temp = new const Reservation * [m_count + 1];
			for (size_t i = 0; i < m_count; i++)
			{
				temp[i] = this->m_reserve[i];
			}
			temp[m_count++] = &res;
			delete[] m_reserve;
			m_reserve = temp;
		}

		return *this;
	}


	ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res)
	{
		bool found = false;
		size_t i = 0;
		for (i = 0; i < m_count && !found; i++) {
			if (m_reserve[i] == &res)
			{
				found = true;
			}
		} 

		if (found)
		{
			for (; i < m_count; i++) {
				m_reserve[i - 1] = m_reserve[i];
			}
			if (m_count)
			{
				m_reserve[--m_count] = nullptr;
			}
			const Reservation** temp;
			temp = new const Reservation * [this->m_count];
			for (size_t i = 0; i < this->m_count; i++)
			{
				if (this->m_reserve[i] != nullptr)
				{
					temp[i] = this->m_reserve[i];
				}
			}
			delete[] this->m_reserve;
			this->m_reserve = new const Reservation * [this->m_count];
			for (size_t i = 0; i < this->m_count; i++)
			{
				this->m_reserve[i] = temp[i];
			}
			delete[] temp;
		}

		return *this;
	}

	size_t ConfirmationSender::size() const
	{
		return m_count;
	}

	ConfirmationSender::~ConfirmationSender()
	{
		delete[] m_reserve;
		m_reserve = nullptr;
	}


	std::ostream& operator<<(std::ostream& os, const ConfirmationSender& confirm)
	{
		os << "--------------------------" << std::endl;
		os << "Confirmations to Send" << std::endl;
		os << "--------------------------" << std::endl;
		if (confirm.size() > 0)
		{
			for (size_t i = 0; i < confirm.size(); i++)
			{
				os << *confirm.m_reserve[i];
			}
			os << "--------------------------" << std::endl;
		}
		else
		{
			os << "There are no confirmations to send!" << std::endl;
			os << "--------------------------" << std::endl;
		}
		return os;
	}

}