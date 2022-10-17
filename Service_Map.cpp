#define _CRT_SECURE_NO_WARNINGS
#include "Storage.h"
#include "Service_Map.h"

Service_Map::Service_Map(DB& db) : Operations(db)
{
}

Service_Map::~Service_Map()
{
}

void Service_Map::save(const Service& service)
{
	char buf[1024];
	if (service.getId() != -1) {
		sprintf(buf,
			"UPDATE service AS s SET s.service = '%s', s.cost = '%s', s.master_id = '%d' WHERE s.id = %d",
			service.getService().c_str(),
			service.getCost().c_str(),
			service.getMasterId(),
			service.getId());
	}
	else {
		sprintf(buf, "INSERT INTO service(service, cost, master_id) VALUES ('%s', '%s', '%d')",
			service.getService().c_str(),
			service.getCost().c_str(),
			service.getMasterId());
	}
	db.execute(buf);
}

void Service_Map::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM service as s WHERE s.id %d", id);
	db.execute(buf);
}

Service* Service_Map::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT s.id, s.service, s.cost, s.master_id FROM service AS s WHERE s.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->service, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->cost, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &this->master_id, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Service order;
		order.setId(id);
		order.setService(reinterpret_cast<char*>(service));
		order.setCost(reinterpret_cast<char*>(cost));
		order.setMasterId(master_id);
		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getService(order.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in order_mapper\n";
	}
	return nullptr;
}

std::vector<Service*> Service_Map::findAll()
{
	std::vector<Service*> service_vector;

	SQLHSTMT statement = db.execute("SELECT s.id, s.service, s.cost, s.master_id FROM service AS");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &service, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &cost, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &master_id, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Service services;
			services.setId(id);
			services.setService(reinterpret_cast<char*>(service));
			services.setCost(reinterpret_cast<char*>(cost));
			services.setMasterId(master_id);

			Storage::getInstance()->putService(services);
			service_vector.push_back(Storage::getInstance()->getService(services.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching client_mapper\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return service_vector;
}
