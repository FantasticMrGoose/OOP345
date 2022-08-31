#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>

namespace sdds
{
	class Book
	{
		std::string m_author{};
		std::string m_title{};
		std::string m_country{};
		size_t m_year{0};
		double m_price{0};
		std::string m_description{};
		void trim(std::string& src);
	public:
		Book() {};
		Book(const std::string& strBook);
		Book(const Book& src); //copy constr
		Book(Book&& src) noexcept; // move constr
		Book& operator=(const Book& src); //copy assign
		Book& operator=(Book&& src) noexcept; //copy move
		~Book() {};

		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();

		//templated spell check
		template <typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_description);
		};

		friend std::ostream& operator<<(std::ostream& os, const Book& book); 
	};
}

#endif // !SDDS_BOOK_H
