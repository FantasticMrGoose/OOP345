/*
	==================================================
	OOP345 Milestone 2
	==================================================
	Name   :Ziran Jeffrey Zhou
	ID     :145117206
	Email  :zjzhou2@myseneca.ca
	Section:NFF

	Date Completed: 11/27/2021

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Station.h"
#pragma once

namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem = 0;
		Item** m_lstItem = nullptr;
		static size_t m_widthField;
	public:
		CustomerOrder() {};
		CustomerOrder(const std::string& in);
		CustomerOrder(const CustomerOrder& src) {
			std::string err = "ERROR: Cannot make copies.";
			throw err;
		}
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(CustomerOrder&& src) noexcept;
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		~CustomerOrder();

		bool isFilled() const; // true if all items in order has been filled

		// all items of ItemName is filled
		bool isItemFilled(const std::string& itemName) const;

		// fill all items in current order
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}


