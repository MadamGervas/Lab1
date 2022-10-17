#pragma once
#ifndef Specialization_HEADER
#define Specialization_HEADER
#include <iostream>
#include <sstream>
#include <string>

class Specialization
{
private:
	long id;
	std::string services_list;
public:
	Specialization();
	~Specialization();

	long getId() const;
	void setId(long);

	std::string getServicesList() const;
	void setServicesList(const std::string& services_list);
};
#endif