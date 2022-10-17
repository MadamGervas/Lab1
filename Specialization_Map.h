#pragma once
#ifndef Specialization_Map_HEADER
#define Specialization_Map_HEADER
#include "Operations.h"
#include "Specialization.h"

#define ID_LEN 8
#define NAME_LEN 1024

class Specialization_Map : public Operations<Specialization, long>
{
private:
	SQLINTEGER id;
	SQLCHAR services_list[128];

public:
	Specialization_Map(DB& db);
	~Specialization_Map();

	void save(const Specialization& specialization) override;
	void remove(long id) override;
	Specialization* findById(long id) override;
	std::vector<Specialization*> findAll() override;
};
#endif