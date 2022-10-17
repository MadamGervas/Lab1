#include "Master.h"

Master::Master()
{
}

Master::~Master()
{
}

long Master::getId() const
{
	return this->id;
}

void Master::setId(long id)
{
	this->id = id;
}

int Master::getStaffId() const
{
	return this->staff_id;
}

void Master::setStaffId(int staff_id)
{
	this->staff_id = staff_id;
}

std::string Master::getSurname() const
{
	return this->surname;
}

void Master::setSurname(const std::string& surname)
{
	this->surname = surname;
}
