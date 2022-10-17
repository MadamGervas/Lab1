#pragma once
#ifndef Materials_Map_HEADER
#define Materials_Map_HEADER
#include "Operations.h"
#include "Materials.h"

#define ID_LEN 8
#define NAME_LEN 1024

class Materials_Map : public Operations<Materials, long>
{
private:
	SQLINTEGER id;
	SQLINTEGER cost;
	SQLCHAR name[64];
	SQLCHAR unit_measurement[64];

public:
	Materials_Map(DB& db);
	~Materials_Map();

	void save(const Materials& materials) override;
	void remove(long id) override;
	Materials* findById(long id) override;
	std::vector<Materials*> findAll() override;

};
#endif