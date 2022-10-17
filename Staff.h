#pragma once
#ifndef Staff_HEADER
#define Staff_HEADER
#include <iostream>
#include <string>
#include <sstream>
#include "Date.h"

class Staff
{
private:
	long id;
	std::string name;
	std::string surname;
	std::string patronymic;
	std::string address;

	Date date_of_birth;
	std::string position;
	int salary;

public:
	Staff();
	~Staff();
	long getId() const;
	void setId(long);

	std::string getName() const;
	void setName(const std::string& name);

	std::string getSurname() const;
	void setSurname(const std::string& surname);

	std::string getPatronymic() const;
	void setPatronymic(const std::string& patronymic);


	std::string getAddress() const;
	void setAddress(const std::string& address);

	Date getDate() const;
	void setDate(Date);
	std::string toStringDate() const;
	Date setStringDate(std::string& order_date);

	std::string getPosition() const;
	void setPosition(const std::string& position);

	int getSalary() const;
	void setSalary(int);
};
#endif