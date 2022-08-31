#ifndef SDDS_RESTAURANT_H
#define SDDS_RESTAURANT_H

#include "Reservation.h"

namespace sdds
{
	class Restaurant
	{
		// Composition with object Reservation
		Reservation* m_reserve{ nullptr };
		size_t m_numRes{ 0 };
	public:
		Restaurant() {};
		Restaurant(const Reservation* reservations[], size_t cnt);
		Restaurant(const Restaurant& src);
		Restaurant& operator=(const Restaurant& src);
		Restaurant(Restaurant&& src) noexcept;
		Restaurant& operator=(Restaurant&& src) noexcept;
		size_t size() const;
		~Restaurant();
		friend std::ostream& operator<<(std::ostream& os, const Restaurant& res);
	};
	
}
#endif // !SDDS_RESTAURANT_H
