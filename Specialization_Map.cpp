#define _CRT_SECURE_NO_WARNINGS
#include "Storage.h"
#include "Specialization_Map.h"

Specialization_Map::Specialization_Map(DB& db) : Operations(db)
{
}

Specialization_Map::~Specialization_Map()
{
}

void Specialization_Map::save(const Specialization& specialization)
{
	char buf[1024];
	if (specialization.getId() != -1) {
		sprintf(buf,
			"UPDATE specialization AS sp SET sp.services_list = '%s' WHERE sp.id = %d",
			specialization.getServicesList().c_str(),
			specialization.getId());
	}
	else {
		sprintf(buf, "INSERT INTO specialization(services_list) VALUES ('%s')",
			specialization.getServicesList().c_str());
	}
	db.execute(buf);
}

void Specialization_Map::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM specialization as s WHERE s.id %d", id);
	db.execute(buf);
}

Specialization* Specialization_Map::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT sp.id, sp.services_list FROM specialization AS sp WHERE sp.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->services_list, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Specialization specialization;
		specialization.setId(id);
		specialization.setServicesList(reinterpret_cast<char*>(services_list));
		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getSpecialization(specialization.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in client_mapper\n";
	}
	return nullptr;
}

std::vector<Specialization*> Specialization_Map::findAll()
{
	std::vector<Specialization*> specialization_vector;

	SQLHSTMT statement = db.execute("SELECT sp.id, sp.services_list FROM specialization AS sp");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &services_list, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Specialization specialization;
			specialization.setId(id);
			specialization.setServicesList(reinterpret_cast<char*>(services_list));

			Storage::getInstance()->putSpecialization(specialization);
			specialization_vector.push_back(Storage::getInstance()->getSpecialization(specialization.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching client_mapper\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return specialization_vector;
}
