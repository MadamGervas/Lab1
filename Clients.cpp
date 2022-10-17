#include "Clients.h"


Clients::Clients()
{
}

Clients::~Clients()
{
}

long Clients::getId() const
{
	return this->id;
}

void Clients::setId(long id)
{
	this->id = id;
}

int Clients::getServiceId() const
{
	return this->service_id;
}

void Clients::setServiceId(int service_id)
{
	this->service_id = service_id;
}

std::string Clients::getName() const
{
	return this->name;
}

void Clients::setName(const std::string& name)
{
	this->name = name;
}

std::string Clients::getSurname() const
{
	return this->surname;
}

void Clients::setSurname(const std::string& surname)
{
	this->surname = surname;
}

std::string Clients::getPatronymic() const
{
	return this->patronymic;
}

void Clients::setPatronymic(const std::string& patronymic)
{
	this->patronymic = patronymic;
}

std::string Clients::getPhoneNumber() const
{
	return this->phone_number;
}

void Clients::setPhoneNumber(const std::string& phone_number)
{
	this->phone_number = phone_number;
}

Timestamp Clients::getOrderTime() const
{
	return this->order_time;
}

void Clients::setOrderTime(Timestamp time)
{
	this->order_time.hour = time.hour;
	this->order_time.min = time.min;
	this->order_time.sec = time.sec;
}

std::string Clients::toStringTime() const
{
	return std::to_string(this->order_time.hour) +
		":" + std::to_string(this->order_time.min) +
		":" + std::to_string(this->order_time.sec);
}

Timestamp Clients::setStringTime(std::string& order_time)
{
	Timestamp strTime;
	std::stringstream in(order_time);
	std::getline(in, order_time, '-');
	strTime.hour = stoi(order_time);
	std::getline(in, order_time, '-');
	strTime.min = stoi(order_time);
	std::getline(in, order_time, '-');
	strTime.sec = stoi(order_time);

	return strTime;
}
