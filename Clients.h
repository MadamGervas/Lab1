#pragma once
#ifndef Clients_HEADER
#define Clients_HEADER
#include <iostream>
#include <sstream>
#include <string>
#include "Timestamp.h"

class Clients
{
private:
	long id;
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string phone_number;
	int service_id;
	Timestamp order_time;

public:
	Clients();
	~Clients();

	long getId() const;
	void setId(long);

	int getServiceId() const;
	void setServiceId(int);

	std::string getName() const;
	void setName(const std::string& name);

	std::string getSurname() const;
	void setSurname(const std::string& surname);

	std::string getPatronymic() const;
	void setPatronymic(const std::string& patronymic);

	std::string getPhoneNumber() const;
	void setPhoneNumber(const std::string& phone_number);

	Timestamp getOrderTime() const;
	void setOrderTime(Timestamp);
	std::string toStringTime() const;
	Timestamp setStringTime(std::string& order_time);
};
#endif
