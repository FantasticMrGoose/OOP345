#include <fstream>
#include <iomanip>
#include "SpellChecker.h"

namespace sdds
{
	SpellChecker::SpellChecker(const char* filename)
	{
		std::ifstream file(filename);
		if (!file)
		{
			const char* err = "Bad file name!";
			throw err;
		}

		size_t cnt = 0;

		while (file && cnt < SIZE)
		{
			file >> m_badWords[cnt] >> m_goodWords[cnt];
			cnt++;
		}
	}

	void SpellChecker::operator()(std::string& text)
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			// keep looking for bad words until npos (end of string)
			while (text.find(m_badWords[i]) != std::string::npos)
			{
				text.replace(text.find(m_badWords[i]), m_badWords[i].length(),
					m_goodWords[i]);
				m_wordsFixed[i]++;
			}
		}
	}

	void SpellChecker::showStatistics(std::ostream& out) const
	{
		out << "Spellchecker Statistics" << std::endl;
		for (size_t i = 0; i < SIZE; i++)
		{
			out << std::setw(15) << std::right << m_badWords[i] << ": " << m_wordsFixed[i] << " replacements" << std::endl;
		}
	}
}