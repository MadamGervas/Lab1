#include "Materials.h"

Materials::Materials()
{
}

Materials::~Materials()
{
}

long Materials::getId() const
{
	return this->id;
}

void Materials::setId(long id)
{
	this->id = id;
}

int Materials::getCost() const
{
	return this->cost;
}

void Materials::setCost(int cost)
{
	this->cost = cost;
}

std::string Materials::getName() const
{
	return this->name;
}

void Materials::setName(const std::string& name)
{
	this->name = name;
}

std::string Materials::getUnitMeasurement() const
{
	return this->unit_measurement;
}

void Materials::setUnitMeasurement(const std::string& unit_measurement)
{
	this->unit_measurement = unit_measurement;
}
