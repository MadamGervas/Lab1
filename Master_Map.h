#pragma once
#ifndef Master_Map_HEADER
#define Master_Map_HEADER
#include "Operations.h"
#include "Master.h"
#include "Specialization_Map.h"
#include "Materials_Map.h"


#define ID_LEN 8
#define NAME_LEN 1024

class Master_Map : public Operations<Master, long>
{
private:
	SQLINTEGER id;
	SQLINTEGER staff_id;
	SQLCHAR surname[32];
	Specialization_Map& specialization_map;
	Materials_Map& materials_map;

public:
	Master_Map(DB& db, Specialization_Map& specialization_map, Materials_Map& materials_map);
	~Master_Map();

	void save(const Master& master) override;
	void remove(long id) override;
	Master* findById(long id) override;
	std::vector<Master*> findAll() override;

	void addMaterials(long id, long materialId, long quantity);
	void addSpecialization(long id, long specializationId);

	void removeMaterials(long id, long materialId, long quantity);
	void removeSpecialization(long id, long specializationId);
};
#endif
