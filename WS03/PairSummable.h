#ifndef SDDS_PAIR_SUMMABLE_H
#define SDDS_PAIR_SUMMABLE_H

#include <string>
#include "Pair.h"

namespace sdds
{
	template<typename V, typename K>
	class PairSummable : public Pair<V, K>
	{
		static V initial;
		static size_t m_minWidth;
	public:
		PairSummable() {};
		PairSummable(const K& key, const V& value = initial)
			:Pair<V, K>(key, value) {
			if (key.size() > m_minWidth)
				m_minWidth = key.size();
		};

		bool isCompatibleWith(const PairSummable<V, K>& b) const {
			return b.key() == this->key();
		};

		PairSummable<V, K>& operator+=(const PairSummable<V, K>& b) {

			//adds the current object value, and the source object value 
			//to creates a new object of PairSummable 
			//and assigns the combined new object to current object
			*this = PairSummable(this->key(), this->value() + b.value()); 
			return *this;
		};

		void display(std::ostream& os) const {
			os << std::left << std::setw(m_minWidth);
			Pair<V, K>::display(os);
			os << std::right;
		};
	};

	template<typename V, typename K>
	size_t PairSummable<V, K>::m_minWidth = 0; //static variables

	template<typename V, typename K>
	V PairSummable<V, K>::initial{}; //static variables

	template<> //specializaiton
	PairSummable<std::string, std::string>& PairSummable<std::string, std::string>::operator+=(const PairSummable<std::string, std::string>& b) {
		if (value() != "")
		{
			*this = PairSummable(this->key(), this->value() + ", " + b.value());
		}
		else
		{
			*this = PairSummable(this->key(), b.value());
		}
		return *this;
	};

}
#endif // !SDDS_PAIR_SUMMABLE_H
