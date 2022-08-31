#include <iomanip>
#include "Book.h"

namespace sdds
{
	void Book::trim(std::string& src)
	{
		size_t begin = src.find_first_not_of(' ');
		size_t end = src.find_last_not_of(' ');
		src = src.substr(begin, (end - begin + 1));
	}

	Book::Book(const std::string& strBook)
	{
		std::string temp = strBook;

		m_author = temp.substr(0, temp.find(","));
		temp = temp.substr(temp.find(",") + 1, temp.length());
		trim(m_author);

		m_title = temp.substr(0, temp.find(","));
		temp = temp.substr(temp.find(",") + 1, temp.length());
		trim(m_title);

		m_country = temp.substr(0, temp.find(","));
		temp = temp.substr(temp.find(",") + 1, temp.length());
		trim(m_country);
		
		m_price = std::stod(temp.substr(0, temp.find(",")));
		temp = temp.substr(temp.find(",") + 1, temp.length());

		m_year = std::stoi(temp.substr(0, temp.find(",")));
		temp = temp.substr(temp.find(",") + 1, temp.length());

		m_description = temp;
		trim(m_description);
	}

	Book::Book(const Book& src)
	{
		*this = src;
	}

	Book::Book(Book&& src) noexcept
	{
		*this = std::move(src);
	}

	Book& Book::operator=(const Book& src)
	{
		if (this != &src)
		{
			this->m_author = src.m_author;
			this->m_title = src.m_title;
			this->m_country = src.m_country;
			this->m_year = src.m_year;
			this->m_price = src.m_price;
			this->m_description = src.m_description;
		}
		return *this;
	}

	Book& Book::operator=(Book&& src) noexcept
	{
		if (this != &src)
		{
			this->m_author = src.m_author;
			this->m_title = src.m_title;
			this->m_country = src.m_country;
			this->m_year = src.m_year;
			this->m_price = src.m_price;
			this->m_description = src.m_description;

			src.m_author.clear();
			src.m_title.clear();
			src.m_country.clear();
			src.m_year = 0u;
			src.m_price = -1;
			src.m_description.clear();
		}
		return *this;
	}

	const std::string& Book::title() const
	{
		return m_title;
	}

	const std::string& Book::country() const
	{
		return m_country;
	}

	const size_t& Book::year() const
	{
		return m_year;
	}

	double& Book::price()
	{
		return m_price;
	}


	std::ostream& operator<<(std::ostream& os, const Book& book)
	{
		os << std::setw(20) << std::right << book.m_author << " | "
			<< std::setw(22) << std::right << book.m_title << " | "
			<< std::setw(5) << std::right << book.m_country << " | "
			<< std::setw(4) << book.m_year << " | "
			<< std::setw(6) << std::right << std::fixed << std::setprecision(2) << book.m_price << " | "
			<< std::left << book.m_description << std::endl;
		
		return os;
	}

}