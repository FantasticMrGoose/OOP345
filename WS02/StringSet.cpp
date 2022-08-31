#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include "StringSet.h"

namespace sdds
{
	StringSet::StringSet(){
		m_strings = {};
		m_numString = 0;
	}

	StringSet::StringSet(const std::string& name)
	{
		m_strings = {};
		m_numString = 1;
		char ch;
		std::ifstream in(name.c_str());
		if (in.is_open())
		{
			while (in.get(ch)) {
				if (ch == ' ')
				{
					this->m_numString++;
				}
			};
			in.clear();
			in.seekg(std::ios::beg);
			this->m_strings = new std::string[m_numString];

			for (auto i = 0u; i < m_numString; i++)
			{
				std::getline(in, m_strings[i], ' ');
			}
		}

	}

	StringSet::StringSet(const StringSet& src)
	{
		*this = src;
	}

	StringSet::StringSet(StringSet&& src) noexcept
	{
		*this = std::move(src);
	}

	StringSet& StringSet::operator=(const StringSet& src)
	{
		if (this != &src)
		{
			this->m_numString = src.m_numString;

			delete[] m_strings;
			m_strings = nullptr;

			if (this->m_numString != 0)
			{
				this->m_strings = new std::string[m_numString];
				for (auto i = 0u; i < m_numString; i++)
				{
					m_strings[i] = src.m_strings[i];
				}
			}
		}
		return *this;
	}

	StringSet& StringSet::operator=(StringSet&& src) noexcept
	{
		if (this != &src)
		{
			delete[] m_strings;
			m_strings = src.m_strings;
			src.m_strings = nullptr;

			this->m_numString = src.m_numString;
			src.m_numString = 0u;
		}

		return *this;
	}

	size_t StringSet::size()
	{
		return m_numString;
	}

	std::string StringSet::operator[](size_t num)
	{
		return num < this->m_numString ? this->m_strings[num] : std::string();
	}

	StringSet::~StringSet()
	{
		if (m_strings)
		{
			delete[] m_strings;
		}
	}
}