#include <string>
#include <iostream>

#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

namespace sdds
{
	class Movie
	{
		std::string m_title{};
		size_t m_year{ 0 };
		std::string m_desc{};
		void trim(std::string& src);
	public:
		Movie() {};
		Movie(const std::string& strMovie);
		Movie(const Movie& src); //copy constr
		Movie(Movie&& src) noexcept; // move constr
		Movie& operator=(const Movie& src); //copy assign
		Movie& operator=(Movie&& src) noexcept; // move assign
		~Movie() {};

		const std::string& title() const;

		template <typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_desc);
			spellChecker(m_title);
		};
		
		friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
	};
}

#endif // !SDDS_MOVIE_H



