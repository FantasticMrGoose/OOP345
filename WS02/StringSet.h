#ifndef SDDS_STRINGSET_H
#define SDDS_STRINGSET_H

#include <string>

namespace sdds
{
	class StringSet
	{
		size_t m_numString{};
		std::string* m_strings{};
	public:
		StringSet();
		StringSet(const std::string& name);
		StringSet(const StringSet&); //copy constr
		StringSet(StringSet&& src) noexcept; // move constructor
		StringSet& operator=(const StringSet&); //copy assign
		StringSet& operator=(StringSet&&) noexcept; // move assignment 
		size_t size();
		std::string operator[](size_t num);
		~StringSet();
	};
}
#endif // !SDDS_STRINGSET_H
