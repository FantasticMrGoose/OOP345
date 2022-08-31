#ifndef SDDS_SETSUMMABLE_H
#define SDDS_SETSUMMABLE_H

#include <string>
#include "Set.h"

namespace sdds
{
	template <size_t N, typename T>
	class SetSummable :public Set<N, T>
	{
	public:
		T accumulate(const std::string& filter) const {
			T accumulator(filter);
			for (size_t i = 0; i < this->size(); i++)
			{
				if (this->get(i).isCompatibleWith(accumulator))
				{
					accumulator += this->get(i);
				}
			}
			return accumulator;
		}
	};

}
#endif // !SDDS_SET_SUMMABLE_H
