#pragma once
#ifndef Service_Map_HEADER
#define Service_Map_HEADER
#include "Operations.h"
#include "Service.h"

#define ID_LEN 8
#define NAME_LEN 1024

class Service_Map : public Operations<Service, long>
{
private:
	SQLINTEGER id;
	SQLCHAR service[64];
	SQLCHAR cost[64];
	SQLINTEGER master_id;
public:
	Service_Map(DB& db);
	~Service_Map();

	void save(const Service& service) override;
	void remove(long id) override;
	Service* findById(long id) override;
	std::vector<Service*> findAll() override;

};
#endif