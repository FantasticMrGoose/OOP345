#ifndef SDDS_SET_H
#define SDDS_SET_H

namespace sdds
{
	template <size_t N, typename T>
	class Set
	{
		T m_elem[N] {};
		size_t m_noElem{ 0u };
	public:
		size_t size() const {
			return m_noElem;
		};

		const T& get(size_t idx) const {
			return m_elem[idx];
		};

		void operator+=(const T& item) {
			if (m_noElem < N)
			{
				m_elem[m_noElem++] = item;
			}
		};
	};
}

#endif // !SDDS_SET_H
