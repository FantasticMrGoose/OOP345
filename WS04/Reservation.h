#ifndef SDDS_RESERVATION_H
#define SDDS_RESERVATION_H

#include <string>
namespace sdds
{
	class Reservation
	{
		std::string m_id{};
		std::string m_name{};
		std::string m_email{};
		size_t m_numPeople{};
		size_t m_partyDay{};
		size_t m_partyHour{};
		void trim(std::string& src);
	public:
		Reservation() {};
		Reservation(const std::string& res);
		Reservation(const Reservation& src);
		Reservation& operator=(const Reservation& src);
		Reservation(Reservation&& src) noexcept;
		Reservation& operator=(Reservation&& src) noexcept;
		void update(int day, int time);
		~Reservation() {};

		friend std::ostream& operator<<(std::ostream& os,
			const Reservation& res);
	};
}

#endif // !SDDS_RESERVATION_H
