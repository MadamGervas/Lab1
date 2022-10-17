#include "Staff.h"

Staff::Staff()
{
}

Staff::~Staff()
{
}

long Staff::getId() const
{
	return this->id;
}

void Staff::setId(long)
{
	this->id = id;
}

std::string Staff::getName() const
{
	return this->name;
}

void Staff::setName(const std::string& name)
{
}

std::string Staff::getSurname() const
{
	return this->surname;
}

void Staff::setSurname(const std::string& surname)
{
}

std::string Staff::getPatronymic() const
{
	return this->patronymic;
}

void Staff::setPatronymic(const std::string& patronymic)
{
}

std::string Staff::getAddress() const
{
	return this->address;
}

void Staff::setAddress(const std::string& address)
{
}

Date Staff::getDate() const
{
	return this->date_of_birth;
}

void Staff::setDate(Date)
{
}

std::string Staff::toStringDate() const
{
	return std::to_string(this->date_of_birth.year) +
		"-" + std::to_string(this->date_of_birth.month) +
		"-" + std::to_string(this->date_of_birth.day);
}

Date Staff::setStringDate(std::string& date_of_birth)
{
	Date strDate;
	std::stringstream in(date_of_birth);
	std::getline(in, date_of_birth, '-');
	strDate.year = stoi(date_of_birth);
	std::getline(in, date_of_birth, '-');
	strDate.month = stoi(date_of_birth);
	std::getline(in, date_of_birth, '-');
	strDate.day = stoi(date_of_birth);

	return strDate;
}

std::string Staff::getPosition() const
{
	return this->position;
}

void Staff::setPosition(const std::string& position)
{
}

int Staff::getSalary() const
{
	return this->salary;
}

void Staff::setSalary(int salary)
{
	this->salary = salary;
}
