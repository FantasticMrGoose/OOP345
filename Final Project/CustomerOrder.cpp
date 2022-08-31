#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const std::string& in)
	{
		Utilities utl;

		size_t pos = 0;
		bool more = false;
		std::string temp;

		try
		{
			m_name = utl.extractToken(in, pos, more);
			m_product = utl.extractToken(in, pos, more);

			// count # of delimiters left, which can be used to find # of items left. 
			temp = in.substr(pos, std::string::npos);
			m_cntItem = std::count(temp.begin(), temp.end(), utl.getDelimiter()) + 1;

			m_lstItem = new Item * [m_cntItem];

			for (size_t i = 0; i < m_cntItem && more; i++)
			{
				m_lstItem[i] = new Item(utl.extractToken(in, pos, more));
			}
			
			CustomerOrder::m_widthField = std::max(utl.getFieldWidth(), m_widthField);
		}
		catch (const std::string error)
		{
			std::cout << error << std::endl;
		}
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src)
		{
			for (size_t i = 0; i < this->m_cntItem; i++)
			{
				delete this->m_lstItem[i];
			}
			delete[] m_lstItem;
			
			this->m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;

			this->m_name = src.m_name;
			this->m_product = src.m_product;
			this->m_cntItem = src.m_cntItem;

			src.m_name.clear();
			src.m_product.clear();
			src.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < this->m_cntItem; i++)
		{
			delete this->m_lstItem[i];
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isFilled() const
	{
		return std::all_of(m_lstItem, m_lstItem + m_cntItem, [](const Item* src) {
			return src->m_isFilled; });	
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filled = true;
		// if any of the orders matching itemName is NOT filled, filled is false. 
		if (std::any_of(m_lstItem, m_lstItem + m_cntItem, [=](const Item* item) {
			return item->m_itemName == itemName && !item->m_isFilled; }))
		{
			filled = false;
		}
		return filled;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					std::cout << "    Filled " << m_name << ", " << m_product <<" [" 
						<< m_lstItem[i]->m_itemName << "]"
						<< std::endl;
				}
				else
				{
					std::cout << "    Unable to fill " << m_name << ", " << m_product 
						<< " [" << m_lstItem[i]->m_itemName << "]"
						<< std::endl;;
				}
			}	
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		std::for_each(m_lstItem, m_lstItem + m_cntItem, [&os](const Item* item) {
			os << "[" << std::setfill('0') << std::setw(6) << std::right << item->m_serialNumber << "] "
				<< std::setw(m_widthField) << std::setfill(' ') << std::left << item->m_itemName << " - ";
			if (item->m_isFilled)
			{
				os << "FILLED";
			}
			else
			{
				os << "TO BE FILLED";
			}
			os << std::endl;
			});
	}
}