#pragma once
#ifndef Staff_Transfer_HEADER
#define Staff_Transfer_HEADER
#include <iostream>
#include <string>
#include <sstream>
#include "Date.h"

class Staff_Transfer
{
private:
	long id;
	std::string position;
	std::string reason;
	std::string number;

	Date order_date;

public:
	Staff_Transfer();
	~Staff_Transfer();
	long getId() const;
	void setId(long);

	std::string getPosition() const;
	void setPosition(const std::string& position);

	std::string getReason() const;
	void setReason(const std::string& reason);


	std::string getNumber() const;
	void setNumber(const std::string& number);

	Date getDate() const;
	void setDate(Date);
	std::string toStringDate() const;
	Date setStringDate(std::string& order_date);
};
#endif