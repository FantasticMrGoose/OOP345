#pragma once

#include <deque>

#include "CustomerOrder.h"
#include "Station.h"

extern std::deque<sdds::CustomerOrder> pending;
extern std::deque<sdds::CustomerOrder> completed;
extern std::deque<sdds::CustomerOrder> incomplete;

namespace sdds
{
	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{ nullptr };
	public:
		Workstation() : Station() {};
		Workstation(const std::string& in) : Station(in) {};
		Workstation(const Workstation& src) = delete;
		Workstation& operator=(const Workstation& src) = delete;
		Workstation(Workstation&& src) noexcept = delete;
		Workstation& operator=(Workstation&& src) noexcept = delete;
		~Workstation() {};

		// fills the order at the front
		void fill(std::ostream& os);

		// moves order at front to next station
		bool attemptToMoveOrder();

		//sets the next station to value of param
		void setNextStation(Workstation* station);

		//returns the next station
		Workstation* getNextStation() const;

		void display(std::ostream& os) const;

		// adds a new order to the workstation
		Workstation& operator+=(CustomerOrder&& newOrder);
	};

}

