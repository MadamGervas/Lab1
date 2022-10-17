#include "Specialization.h"

Specialization::Specialization()
{
}

Specialization::~Specialization()
{
}

long Specialization::getId() const
{
	return this->id;
}

void Specialization::setId(long id)
{
	this->id = id;
}

std::string Specialization::getServicesList() const
{
	return this->services_list;
}

void Specialization::setServicesList(const std::string& services_list)
{
	this->services_list = services_list;
}
