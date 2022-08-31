#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include "TimedEvents.h"

namespace sdds
{
	void TimedEvents::startClock()
	{
		m_startTime = std::chrono::steady_clock::now();
	}

	void TimedEvents::stopClock() 
	{
		m_endTime = std::chrono::steady_clock::now();
	}

	void TimedEvents::addEvent(const char* name)
	{
		auto timeDiff = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);
		if (m_numEvents < max_events)
		{
			this->events[m_numEvents].m_eventName = name;
			this->events[m_numEvents].m_unitOfTime = "nanoseconds";
			this->events[m_numEvents].m_duration = timeDiff;
			m_numEvents++;
		}
	}
	
	std::ostream& operator<<(std::ostream& os, const TimedEvents& evt)
	{
		os << "--------------------------\n";
		os << "Execution Times:\n";
		os << "--------------------------\n";
		for (int i = 0; i < evt.m_numEvents; i++)
		{
			os << std::setw(21) << std::left
			<< evt.events[i].m_eventName << ' ' << std::setw(13) << std::right
			<< evt.events[i].m_duration.count() << ' '
			<< evt.events[i].m_unitOfTime << '\n';
		}
		os << "--------------------------\n";
		return os;
	}
}