#include "Service.h"

Service::Service()
{
}

Service::~Service()
{
}

long Service::getId() const
{
	return this->id;
}

void Service::setId(long)
{
	this->id = id;
}

std::string Service::getService() const
{
	return this->service;
}

void Service::setService(const std::string& service)
{
	this->service = service;
}

std::string Service::getCost() const
{
	return this->cost;
}

void Service::setCost(const std::string& cost)
{
	this->cost = cost;
}

int Service::getMasterId() const
{
	return this->master_id;
}

void Service::setMasterId(int)
{
	this->master_id = master_id;
}
