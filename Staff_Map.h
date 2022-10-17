#pragma once
#ifndef Staff_Map_HEADER
#define Staff_Map_HEADER
#include "Operations.h"
#include "Staff.h"

#define ID_LEN 8
#define NAME_LEN 1024


class Staff_Map : public Operations<Staff, long>
{
private:
	SQLINTEGER id;
	SQLCHAR name[64];
	SQLCHAR surname[32];
	SQLCHAR patronymic[64];
	SQLCHAR address[64];
	SQLCHAR date_of_birth[32];
	SQLCHAR position[64];
	SQLINTEGER salary;
public:
	Staff_Map(DB& db);
	~Staff_Map();

	void save(const Staff& staff) override;
	void remove(long id) override;
	Staff* findById(long id) override;
	std::vector<Staff*> findAll() override;
};
#endif