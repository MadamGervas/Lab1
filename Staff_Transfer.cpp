#include "Staff_Transfer.h"


Staff_Transfer::Staff_Transfer()
{
}

Staff_Transfer::~Staff_Transfer()
{
}

long Staff_Transfer::getId() const
{
	return this->id;
}

void Staff_Transfer::setId(long id)
{
	this->id = id;
}

std::string Staff_Transfer::getPosition() const
{
	return this->position;
}

void Staff_Transfer::setPosition(const std::string& position)
{
	this->position = position;
}

std::string Staff_Transfer::getReason() const
{
	return this->reason;
}

void Staff_Transfer::setReason(const std::string& reason)
{
	this->reason = reason;
}

std::string Staff_Transfer::getNumber() const
{
	return this->number;
}

void Staff_Transfer::setNumber(const std::string& number)
{
	this->number = number;
}

Date Staff_Transfer::getDate() const
{
	return this->order_date;
}

void Staff_Transfer::setDate(Date date)
{
	this->order_date.day = date.day;
	this->order_date.month = date.month;
	this->order_date.year = date.year;
}

std::string Staff_Transfer::toStringDate() const
{
	return std::to_string(this->order_date.year) +
		"-" + std::to_string(this->order_date.month) +
		"-" + std::to_string(this->order_date.day);
}

Date Staff_Transfer::setStringDate(std::string& order_date)
{
	Date strDate;
	std::stringstream in(order_date);
	std::getline(in, order_date, '-');
	strDate.year = stoi(order_date);
	std::getline(in, order_date, '-');
	strDate.month = stoi(order_date);
	std::getline(in, order_date, '-');
	strDate.day = stoi(order_date);

	return strDate;
}
