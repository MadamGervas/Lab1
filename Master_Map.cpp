#define _CRT_SECURE_NO_WARNINGS
#include "Storage.h"
#include "Master_Map.h"


Master_Map::Master_Map(
	DB& db, Specialization_Map& specialization_map, Materials_Map& materials_map) : 
	Operations(db), specialization_map(specialization_map), materials_map(materials_map)
{

}

Master_Map::~Master_Map()
{
}

void Master_Map::save(const Master& master)
{
	char buf[1024];
	if (master.getId() != -1) {
		sprintf(buf,
			"UPDATE master AS m SET m.staff_id = '%d', m.surname = '%s' WHERE m.id = %d",
			master.getId(),
			master.getStaffId(),
			master.getSurname().c_str());
	}
	else {
		sprintf(buf, "INSERT INTO master(staff_id, surname) VALUES ('%d', '%s')",
			master.getStaffId(),
			master.getSurname().c_str());
	}
	db.execute(buf);
}

void Master_Map::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM master as m WHERE m.id %d", id);
	db.execute(buf);
}

Master* Master_Map::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT m.id, m.staff_id, m.surname FROM master AS m WHERE m.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->staff_id, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->surname, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Master master;
		master.setId(id);
		master.setStaffId(staff_id);
		master.setSurname(reinterpret_cast<char*>(surname));
		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getMaster(master.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in masters_mapper\n";
	}
	return nullptr;
}

std::vector<Master*> Master_Map::findAll()
{
	std::vector<Master*> masters_vector;

	SQLHSTMT statement = db.execute("SELECT m.id, m.staff_id, m.surname FROM master AS m");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &staff_id, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &surname, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Master master;
			master.setId(id);
			master.setStaffId(staff_id);
			master.setSurname(reinterpret_cast<char*>(surname));

			Storage::getInstance()->putMaster(master);
			masters_vector.push_back(Storage::getInstance()->getMaster(master.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching master\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return masters_vector;
}

void Master_Map::addMaterials(long id, long materialId, long quantity)
{
	char buf[128];
	sprintf(buf, "INSERT INTO master_materials(masters_id, materials_id, quantity) values (%d, %d, %d)", id, materialId, quantity);
	db.execute(buf);

}

void Master_Map::addSpecialization(long id, long specializationId)
{
	char buf[128];
	sprintf(buf, "INSERT INTO master_specialization(master_id, specialization_id) values (%d, %d)", id, specializationId);
	db.execute(buf);
}

void Master_Map::removeMaterials(long id, long materialId, long quantity)
{
	char buf[128];
	sprintf(buf, "DELETE FROM master_materials WHERE (masters_id = %d AND materials_id = %d AND quantity = %d)", id, materialId, quantity);
	db.execute(buf);
}

void Master_Map::removeSpecialization(long id, long specializationId)
{
	char buf[128];
	sprintf(buf, "DELETE FROM master_specialization WHERE (master_id = %d AND specialization_id = %d)", id, specializationId);
	db.execute(buf);
}
