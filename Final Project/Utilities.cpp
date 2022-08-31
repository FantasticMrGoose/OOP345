#include "Utilities.h"

namespace sdds
{
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token;
		size_t start_pos = next_pos;

		//finds the delimiter after the start position
		next_pos = str.find(m_delimiter, start_pos);

		token = str.substr(start_pos, (next_pos - start_pos));
		m_widthField = std::max(m_widthField, token.length());
		if (str.at(start_pos) == m_delimiter)
		{
			std::string error = "Delimiter found!";
			more = false;
			throw error;
		}
		else if (next_pos == std::string::npos)
		{
			more = false;		
		}
		else
		{
			more = true;
		}
		next_pos++;

		return token;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

}