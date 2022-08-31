#include <iostream>
#include <string>

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

namespace sdds
{
	template <typename T>
	class Collection
	{
		std::string m_name{};
		T* m_item{ nullptr };
		size_t m_cnt{ 0 };
		void (*observer)(const Collection<T>&, const T&) {
			nullptr
		};
	public:
		Collection() {};
		Collection(const std::string& name) : m_name{ name }, m_item{ nullptr },
			m_cnt{ 0 }, observer{ nullptr } {}
		Collection(const Collection& src) = delete;
		Collection& operator=(const Collection& src) = delete;
		~Collection() {
			delete[] m_item;
		}

		const std::string& name() const {
			return m_name;
		}

		size_t size() const {
			return m_cnt;
		}

		void setObserver(void (*observer)(const Collection<T>&, const T&)) {
			// pointing to a different function
			this->observer = observer;
		}

		Collection<T>& operator+=(const T& item) {
			bool found = false;
			for (size_t i = 0; i < this->m_cnt && !found; i++)
			{
				if (this->m_item[i].title() == item.title()) {
					found = true;
				}
			}

			// method shown in class
			if (!found)
			{
				T* temp = new T[this->m_cnt + 1];
				for (size_t i = 0; i < this->m_cnt; i++)
				{
					temp[i] = this->m_item[i];
				}
				temp[this->m_cnt++] = item;
				delete[] this->m_item;
				this->m_item = temp;

				if (this->observer)
				{
					this->observer(*this, item);
				}
			}
			return *this;
		}

		T& operator[](size_t idx) const {
			if (idx >= size())
			{
				std::string err;
				err = "Bad index [" + std::to_string(idx) + "]. Collection has ["
					+ std::to_string(m_cnt) + "] items.";
				throw std::out_of_range(err);
			}
			else
			{
				return m_item[idx];
			}
		}

		T* operator[](const std::string& title) const {
			bool found = false;
			size_t idx;
			for (size_t i = 0; i < m_cnt && !found; i++)
			{
				if (m_item[i].title() == title)
				{
					found = true;
					idx = i;
				}
			}
			return found ? &m_item[idx] : nullptr;
		}
	};

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Collection<T>& collect) {
		for (size_t i = 0; i < collect.size(); i++)
		{
			os << collect[i];
		}
		return os;
	}
}

#endif // !SDDS_COLLECTION_H




