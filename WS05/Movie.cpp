#include <iomanip>
#include "Movie.h"

namespace sdds
{
	void Movie::trim(std::string& src)
	{
		size_t begin = src.find_first_not_of(' ');
		size_t end = src.find_last_not_of(' ');
		src = src.substr(begin, (end - begin + 1));
	}

	Movie::Movie(const std::string& strMovie)
	{
		std::string temp = strMovie;

		m_title = temp.substr(0, temp.find(","));
		temp = temp.substr(temp.find(",") + 1, temp.length());
		trim(m_title);

		m_year = std::stoi(temp.substr(0, temp.find(",")));
		temp = temp.substr(temp.find(",") + 1, temp.length());

		m_desc = temp;
		trim(m_desc);
	}

	Movie::Movie(const Movie& src)
	{
		*this = src;
	}

	Movie::Movie(Movie&& src) noexcept
	{
		*this = std::move(src);
	}

	Movie& Movie::operator=(const Movie& src)
	{
		if (this != &src)
		{
			this->m_title = src.m_title;
			this->m_year = src.m_year;
			this->m_desc = src.m_desc;
		}
		return *this;
	}

	Movie& Movie::operator=(Movie&& src) noexcept
	{
		if (this != &src)
		{
			this->m_title = src.m_title;
			this->m_year = src.m_year;
			this->m_desc = src.m_desc;

			src.m_title.clear();
			src.m_year = 0;
			src.m_desc.clear();
		}
		return *this;
	}

	const std::string& Movie::title() const
	{
		return m_title;
	}


	std::ostream& operator<<(std::ostream& os, const Movie& movie)
	{
		os << std::setw(40) <<std::right << movie.m_title << " | "
			<< std::setw(4) << movie.m_year << " | "
			<< std::left << movie.m_desc << std::endl;
		return os;
	}

}