#pragma once
#ifndef Materials_HEADER
#define Materials_HEADER
#include <iostream>
#include <string>

class Materials
{
private:
	long id;
	int cost;
	std::string name;
	std::string unit_measurement;

public:
	Materials();
	~Materials();

	long getId() const;
	void setId(long);

	int getCost() const;
	void setCost(int);

	std::string getName() const;
	void setName(const std::string& name);

	std::string getUnitMeasurement() const;
	void setUnitMeasurement(const std::string& unit_measurement);
};
#endif