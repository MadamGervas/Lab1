#pragma once
#ifndef Master_HEADER
#define Master_HEADER
#include <iostream>
#include <string>

class Master
{
private:
	long id;
	std::string surname;
	int staff_id;

public:
	Master();
	~Master();

	long getId() const;
	void setId(long);

	std::string getSurname() const;
	void setSurname(const std::string& surname);

	int getStaffId() const;
	void setStaffId(int);
};
#endif
