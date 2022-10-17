#pragma once
#ifndef Service_HEADER
#define Service_HEADER
#include <iostream>
#include <string>

class Service
{
private:
	long id;
	std::string service;
	std::string cost;
	int master_id;

public:
	Service();
	~Service();

	long getId() const;
	void setId(long);

	std::string getService() const;
	void setService(const std::string& service);

	std::string getCost() const;
	void setCost(const std::string& cost);

	int getMasterId() const;
	void setMasterId(int);
};
#endif
