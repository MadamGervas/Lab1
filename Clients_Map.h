#pragma once
#ifndef Clients_Map_HEADER
#define Clients_Map_HEADER
#include "Operations.h"
#include "Clients.h"

#define ID_LEN 8
#define NAME_LEN 1024

class Clients_Map : public Operations<Clients, long>
{
private:
	SQLINTEGER id;
	SQLINTEGER service_id;
	SQLCHAR name[64];
	SQLCHAR surname[64];
	SQLCHAR patronymic[64];
	SQLCHAR phone_number[12];
	SQLCHAR order_time[16];

public:
	Clients_Map(DB& db);
	~Clients_Map();

	void save(const Clients& client) override;
	void remove(long id) override;
	Clients* findById(long id) override;
	std::vector<Clients*> findAll() override;
};
#endif