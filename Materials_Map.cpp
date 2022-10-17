#define _CRT_SECURE_NO_WARNINGS
#include "Storage.h"
#include "Materials_Map.h"

Materials_Map::Materials_Map(DB& db) : Operations(db)
{
}

Materials_Map::~Materials_Map()
{
}

void Materials_Map::save(const Materials& materials)
{
	char buf[1024];
	if (materials.getId() != -1) {
		sprintf(buf,
			"UPDATE materials AS m SET m.name = '%s', m.unit_measurement = '%s', m.cost = '%d' WHERE m.id = %d",
			materials.getName().c_str(),
			materials.getUnitMeasurement().c_str(),
			materials.getCost(),
			materials.getId());
	}
	else {
		sprintf(buf, "INSERT INTO materials(name, unit_measurement, cost) VALUES ('%s', '%s', '%d')",
			materials.getName().c_str(),
			materials.getUnitMeasurement().c_str(),
			materials.getCost(),
			materials.getId());
	}
	db.execute(buf);
}

void Materials_Map::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM materials as m WHERE m.id %d", id);
	db.execute(buf);
}

Materials* Materials_Map::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT m.id, m.name, m.unit_measurement, m.cost FROM materials AS m WHERE m.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->unit_measurement, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &this->cost, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Materials materials;
		materials.setId(id);
		materials.setName(reinterpret_cast<char*>(name));
		materials.setUnitMeasurement(reinterpret_cast<char*>(unit_measurement));
		materials.setCost(cost);
		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getMaterials(materials.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in order_mapper\n";
	}
	return nullptr;
}

std::vector<Materials*> Materials_Map::findAll()
{
	std::vector<Materials*> materials_vector;

	SQLHSTMT statement = db.execute("SELECT m.id, m.name, m.unit_measurement, m.cost FROM materials AS m");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &unit_measurement, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &cost, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Materials materials;
			materials.setId(id);
			materials.setName(reinterpret_cast<char*>(name));
			materials.setUnitMeasurement(reinterpret_cast<char*>(unit_measurement));
			materials.setCost(cost);

			Storage::getInstance()->putMaterials(materials);
			materials_vector.push_back(Storage::getInstance()->getMaterials(materials.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching client_mapper\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return materials_vector;
}
