#ifndef SDDS_CONFIRMATION_SENDER_H
#define SDDS_CONFIRMATION_SENDER_H

#include "Reservation.h"
namespace sdds
{
	
	class ConfirmationSender
	{
		// Aggregation with object Reservation
		const sdds::Reservation** m_reserve{nullptr};
		size_t m_count{ 0 };
	public:
		ConfirmationSender() {};
		ConfirmationSender(const ConfirmationSender& src);
		ConfirmationSender& operator=(const ConfirmationSender& src);
		ConfirmationSender(ConfirmationSender&& src) noexcept;
		ConfirmationSender& operator=(ConfirmationSender&& src) noexcept;
		ConfirmationSender& operator+=(const Reservation& res);
		ConfirmationSender& operator-=(const Reservation& res);
		size_t size() const;
		~ConfirmationSender();

		friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& confirm);
		
	};
}
#endif // !SDDS_RESTAURANT_H