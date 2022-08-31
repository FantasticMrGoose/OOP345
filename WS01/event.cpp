#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <iomanip>
#include "event.h"

size_t g_sysClock = 0;

namespace sdds
{

	void Event::dma_string(const char* src)
	{
		this->m_eventDescrpt = new char[strlen(src) + 1];
		strcpy(this->m_eventDescrpt, src);
	}

	Event::Event(const Event& src)
	{
		if (src.m_eventDescrpt != nullptr) {
			*this = src; // calls copy assignment
		}
	}

	Event& Event::operator=(const Event& src)
	{
		if (this != &src && src.m_eventDescrpt != nullptr)
		{
			if (this->m_eventDescrpt != nullptr)
			{
				delete[] this->m_eventDescrpt;
			}
			dma_string(src.m_eventDescrpt);
			this->m_startTime = src.m_startTime;
		}
		return *this;
	}

	void Event::display() const
	{
		static size_t count = 0; //static to allocate for lifetime of program
		std::cout << std::setw(2) << std::setfill(' ') << ++count << ". ";
		if (m_eventDescrpt)
		{
			std::cout << std::setw(2) << std::setfill('0') 
				<< this->m_startTime / 3600 << ":"
				<< std::setw(2) << std::setfill('0') 
				<< (this->m_startTime % 3600) / 60 << ":"
				<< std::setw(2) << std::setfill('0') 
				<< this->m_startTime % 60 << " => ";
				std::cout << m_eventDescrpt;
		}
		else
		{
			std::cout << "| No Event |";
		}
		std::cout << std::endl;	
	}

	void Event::set(const char* desc)
	{
		m_startTime = ::g_sysClock;
		if (desc)
		{
			if (this->m_eventDescrpt != nullptr)
			{
				delete[] this->m_eventDescrpt;
				this->m_eventDescrpt = nullptr;
			}
			dma_string(desc);
		}
		else
		{
			if (this->m_eventDescrpt != nullptr)
			{
				delete[] this->m_eventDescrpt;
				this->m_eventDescrpt = nullptr;
			}
		}
	}

	Event::~Event()
	{
		if (this->m_eventDescrpt != nullptr)
		{
			delete[] this->m_eventDescrpt;
			this->m_eventDescrpt = nullptr;
		}
	}
}