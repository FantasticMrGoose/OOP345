#include <iostream>
#include <string>

#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H


namespace sdds
{
	const size_t SIZE = 6;
	class SpellChecker
	{
		std::string m_badWords[SIZE]{};
		std::string m_goodWords[SIZE]{};
		size_t m_wordsFixed[SIZE]{ 0 };
	public:
		SpellChecker() {};
		SpellChecker(const char* filename);

		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;
	};

}
#endif // !SDDS_SPELLCHECKER_H
