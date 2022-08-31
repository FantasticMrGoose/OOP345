#include "Workstation.h"

std::deque<sdds::CustomerOrder> pending{};
std::deque<sdds::CustomerOrder> completed{};
std::deque<sdds::CustomerOrder> incomplete{};

namespace sdds
{

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool moved = false;
		if (!m_orders.empty())
		{
			// if the item at station is filled
			if (m_orders.front().isItemFilled(this->getItemName()))
			{
				// if there is a next station
				if (m_pNextStation != nullptr)
				{
					// move to next station
					*m_pNextStation += (std::move(m_orders.front()));
				}
				else
				{
					// if whole order is filled
					if (m_orders.front().isFilled())
					{
						//move to completed
						completed.push_back(std::move(m_orders.front()));
					}
					else
					{
						incomplete.push_back(std::move(m_orders.front()));
					}
				}
				moved = true;
			}
			else if (this->getQuantity() < 1)
			{
				if (m_pNextStation != nullptr)
				{
					*m_pNextStation += (std::move(m_orders.front()));
				}
				else
				{
					incomplete.push_back(std::move(m_orders.front()));
				}
				moved = true;
			}
		}
		if (moved)
		{
			m_orders.pop_front();
		}
		return moved;
	}

	void Workstation::setNextStation(Workstation* station = nullptr)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation != nullptr)
		{
			os << this->getItemName() << " --> " << m_pNextStation->getItemName()
				<< std::endl;
		}
		else
		{
			os << this->getItemName() << " --> End of Line" << std::endl;
		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		this->m_orders.push_back(std::move(newOrder));
		return *this;
	}
}