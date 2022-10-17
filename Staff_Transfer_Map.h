#pragma once
#ifndef Staff_Transfer_Map_HEADER
#define Staff_Transfer_Map_HEADER
#include "Operations.h"
#include "Staff_Transfer.h"

#define ID_LEN 8
#define NAME_LEN 1024


class Staff_Transfer_Map : public Operations<Staff_Transfer, long>
{
private:
	SQLINTEGER id;
	SQLCHAR position[64];
	SQLCHAR reason[128];
	SQLCHAR number[64];
	SQLCHAR order_date[32];
public:
	Staff_Transfer_Map(DB& db);
	~Staff_Transfer_Map();

	void save(const Staff_Transfer& staff_transfer) override;
	void remove(long id) override;
	Staff_Transfer* findById(long id) override;
	std::vector<Staff_Transfer*> findAll() override;
};
#endif