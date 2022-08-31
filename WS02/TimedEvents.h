#ifndef SDDS_TIMEDEVENTS_H
#define SDDS_TIMEDEVENTS_H

#include <iostream>
#include <chrono>
#include <string>

namespace sdds
{
	const int max_events = 10;
	class TimedEvents
	{
		int m_numEvents{ 0 };
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::steady_clock::time_point m_endTime;
		struct Event
		{
			std::string m_eventName{};
			std::string m_unitOfTime{};
			std::chrono::steady_clock::duration m_duration{};
		}events[max_events];
	public:
		TimedEvents() {};
		void startClock();
		void stopClock();
		void addEvent(const char* name);
		friend std::ostream& operator<<(std::ostream& os, const TimedEvents& evt);
	};

}

#endif // !SDDS_TIMEDEVENTS_H
