#define _CRT_SECURE_NO_WARNINGS
#include "Storage.h"
#include "Staff_Map.h"

Staff_Map::Staff_Map(DB& db) : Operations(db)
{
}

Staff_Map::~Staff_Map()
{
}

void Staff_Map::save(const Staff& staff)
{
	char buf[1024];
	if (staff.getId() != -1) {
		sprintf(buf,
			"UPDATE staff AS s SET s.name = '%s', s.surname = '%s', s.patronymic = '%s', s.address = '%s', s.date_of_birth = '%s', s.position = '%s' s.salary = '%d' WHERE s.id = %d",
			staff.getName().c_str(),
			staff.getSurname().c_str(),
			staff.getPatronymic().c_str(),
			staff.getAddress().c_str(),
			staff.toStringDate().c_str(),
			staff.getPosition().c_str(),
			staff.getSalary(),
			staff.getId()
		);
	}
	else {
		sprintf(buf, "INSERT INTO staff(name, surname, patronymic, address, date_of_birth, position, salary) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s')",
			staff.getName().c_str(),
			staff.getSurname().c_str(),
			staff.getPatronymic().c_str(),
			staff.getAddress().c_str(),
			staff.toStringDate().c_str(),
			staff.getPosition().c_str(),
			staff.getSalary());
	}
	db.execute(buf);
}

void Staff_Map::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM staff as s WHERE s.id %d", id);
	db.execute(buf);
}

Staff* Staff_Map::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT s.id, s.name, s.surname, s.patronymic, s.address, s.date_of_birth, s.position, s.salary FROM staff AS s WHERE s.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->surname, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &this->patronymic, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &this->address, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &this->date_of_birth, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_CHAR, &this->position, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 8, SQL_C_CHAR, &this->salary, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Staff staff;
		staff.setId(id);
		staff.setName(reinterpret_cast<char*>(name));
		staff.setSurname(reinterpret_cast<char*>(surname));
		staff.setPatronymic(reinterpret_cast<char*>(patronymic));
		staff.setAddress(reinterpret_cast<char*>(address));
		staff.setPosition(reinterpret_cast<char*>(position));
		staff.setSalary(salary);
		std::string str = reinterpret_cast<char*>(date_of_birth);
		staff.setDate(staff.setStringDate(str));
		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getStaff(staff.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in staff_mapper\n";
	}
	return nullptr;
}

std::vector<Staff*> Staff_Map::findAll()
{
	std::vector<Staff*> staff_vector;

	SQLHSTMT statement = db.execute("SELECT s.id, s.name, s.surname, s.patronymic, s.address, s.date_of_birth, s.position, s.salary FROM staff AS s");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &name, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &surname, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &patronymic, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &address, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 6, SQL_C_CHAR, &date_of_birth, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 7, SQL_C_CHAR, &position, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 8, SQL_C_CHAR, &salary, NAME_LEN, nullptr);

	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Staff staff;
			staff.setId(id);
			staff.setName(reinterpret_cast<char*>(name));
			staff.setSurname(reinterpret_cast<char*>(surname));
			staff.setPatronymic(reinterpret_cast<char*>(patronymic));
			staff.setAddress(reinterpret_cast<char*>(address));
			staff.setPosition(reinterpret_cast<char*>(position));
			staff.setSalary(salary);
			std::string str = reinterpret_cast<char*>(date_of_birth);
			staff.setDate(staff.setStringDate(str));

			Storage::getInstance()->putStaff(staff);
			staff_vector.push_back(Storage::getInstance()->getStaff(staff.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching staff\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return staff_vector;
}
