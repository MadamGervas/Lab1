#define _CRT_SECURE_NO_WARNINGS
#include "Storage.h"
#include "Clients_Map.h"

Clients_Map::Clients_Map(DB& db) : Operations(db)
{
}

Clients_Map::~Clients_Map()
{
}

void Clients_Map::save(const Clients& client)
{
	char buf[1024];
	if (client.getId() != -1) {
		sprintf(buf,
			"UPDATE clients AS c SET c.name = '%s', c.surname = '%s', c.patronymic = '%s', c.phone_number = '%s', c.order_time = '%s', cl.service_id = '%d' WHERE cl.id = %d",
			client.getName().c_str(),
			client.getSurname().c_str(),
			client.getPatronymic().c_str(),
			client.getPhoneNumber().c_str(),
			client.toStringTime().c_str(),
			client.getServiceId(),
			client.getId());
	}
	else {
		sprintf(buf, "INSERT INTO clients(name, surname, patronymic, phone_number, order_time, service_id) VALUES ('%s', '%s', '%s', '%s', '%s', '%d')",
			client.getName().c_str(),
			client.getSurname().c_str(),
			client.getPatronymic().c_str(),
			client.getPhoneNumber().c_str(),
			client.toStringTime().c_str(),
			client.getServiceId());
	}
	db.execute(buf);
}

void Clients_Map::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM clients as c WHERE c.id %d", id);
	db.execute(buf);
}

Clients* Clients_Map::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT c.id, c.name, c.surname, c.patronymic, c.phone_number, c.order_time, c.service_id FROM clients AS c WHERE c.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->surname, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &this->patronymic, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &this->phone_number, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &this->order_time, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_CHAR, &this->service_id, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Clients client;
		client.setId(id);
		client.setName(reinterpret_cast<char*>(name));
		client.setSurname(reinterpret_cast<char*>(surname));
		client.setPatronymic(reinterpret_cast<char*>(patronymic));
		client.setPhoneNumber(reinterpret_cast<char*>(phone_number));
		std::string str = reinterpret_cast<char*>(time);
		client.setOrderTime(client.setStringTime(str));
		client.setServiceId(service_id);
		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getClients(client.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in client_mapper\n";
	}
	return nullptr;
}

std::vector<Clients*> Clients_Map::findAll()
{
	std::vector<Clients*> clients_vector;

	SQLHSTMT statement = db.execute("SELECT c.id, c.name, c.surname, c.patronymic, c.phone_number, c.order_time, c.service_id FROM clients AS c");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &surname, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &patronymic, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &phone_number, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &order_time, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_CHAR, &service_id, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Clients client;
			client.setId(id);
			client.setName(reinterpret_cast<char*>(name));
			client.setSurname(reinterpret_cast<char*>(surname));
			client.setPatronymic(reinterpret_cast<char*>(patronymic));
			client.setPhoneNumber(reinterpret_cast<char*>(phone_number));
			std::string str = reinterpret_cast<char*>(time);
			client.setOrderTime(client.setStringTime(str));
			client.setServiceId(service_id);

			Storage::getInstance()->putClients(client);
			clients_vector.push_back(Storage::getInstance()->getClients(client.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching client_mapper\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return clients_vector;
}
