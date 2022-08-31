#ifndef SDDS_EVENT_H
#define SDDS_EVENT_H

extern size_t g_sysClock; // time of the day: number of seconds since midnight, global var

namespace sdds
{
	class Event
	{
		char* m_eventDescrpt = nullptr;
		size_t m_startTime = 0;
		void dma_string(const char* src); //function to dynamically allocate string
	public:
		Event() {};
		Event(const Event&); //copy constructor
		Event& operator=(const Event&); //copy assignment
		void display() const;
		void set(const char* desc = nullptr);
		~Event();
	};
}

#endif // !SDDS_EVENT_H
