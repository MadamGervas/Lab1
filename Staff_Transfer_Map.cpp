#define _CRT_SECURE_NO_WARNINGS
#include "Storage.h"
#include "Staff_Transfer_Map.h"

Staff_Transfer_Map::Staff_Transfer_Map(DB& db): Operations(db)
{
}

Staff_Transfer_Map::~Staff_Transfer_Map()
{
}

void Staff_Transfer_Map::save(const Staff_Transfer& staff_transfer)
{
	char buf[1024];
	if (staff_transfer.getId() != -1) {
		sprintf(buf,
			"UPDATE staff_transfer AS s SET s.position = '%s', s.reason = '%s', s.number = '%s',  s.order_date = '%s' WHERE s.id = %d",
			staff_transfer.getPosition().c_str(),
			staff_transfer.getReason().c_str(),
			staff_transfer.getNumber().c_str(),
			staff_transfer.toStringDate().c_str(),
			staff_transfer.getId()
		);
	}
	else {
		sprintf(buf, "INSERT INTO staff(position, reason, number, order_date) VALUES ('%s', '%s', '%s', '%s')",
			staff_transfer.getPosition().c_str(),
			staff_transfer.getReason().c_str(),
			staff_transfer.getNumber().c_str(),
			staff_transfer.toStringDate().c_str());
	}
	db.execute(buf);

}

void Staff_Transfer_Map::remove(long id)
{
	char buf[64];
	sprintf(buf, "DELETE FROM staff_transfer as st WHERE st.id %d", id);
	db.execute(buf);
}

Staff_Transfer* Staff_Transfer_Map::findById(long id)
{
	char buf[64];
	sprintf(buf, "SELECT st.id, st.position, st.reason, st.number, st.order_date FROM staff_transfer AS st WHERE st.id = %d", id);

	SQLHSTMT statement = db.execute(buf);
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &this->id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &this->position, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &this->reason, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &this->number, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &this->order_date, NAME_LEN, nullptr);

	retcode = SQLFetch(statement);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		Staff_Transfer staff_transfer;
		staff_transfer.setId(id);
		staff_transfer.setPosition(reinterpret_cast<char*>(position));
		staff_transfer.setReason(reinterpret_cast<char*>(reason));
		staff_transfer.setNumber(reinterpret_cast<char*>(number));
		std::string str = reinterpret_cast<char*>(order_date);
		staff_transfer.setDate(staff_transfer.setStringDate(str));
	
		SQLFreeStmt(statement, SQL_CLOSE);
		return Storage::getInstance()->getStaffTransfer(staff_transfer.getId());
	}
	else if (retcode != SQL_NO_DATA) {
		std::cout << "SearchById error in moving_mapper\n";
	}
	return nullptr;
}

std::vector<Staff_Transfer*> Staff_Transfer_Map::findAll()
{
	std::vector<Staff_Transfer*> staff_transfer_vector;
	
	SQLHSTMT statement = db.execute("SELECT st.id, st.position, st.reason, st.number, st.order_date FROM staff_transfer AS st");
	SQLRETURN retcode;
	retcode = SQLBindCol(statement, 1, SQL_C_LONG, &id, ID_LEN, nullptr);
	retcode = SQLBindCol(statement, 2, SQL_C_CHAR, &position, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 3, SQL_C_CHAR, &reason, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 4, SQL_C_CHAR, &number, NAME_LEN, nullptr);
	retcode = SQLBindCol(statement, 5, SQL_C_CHAR, &order_date, NAME_LEN, nullptr);
	cout << id << endl;


	while (true) {
		retcode = SQLFetch(statement);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			Staff_Transfer staff_transfer;
			staff_transfer.setId(id);
			std::string test = reinterpret_cast<char*>(position);
			staff_transfer.setPosition(reinterpret_cast<char*>(position));
			staff_transfer.setReason(reinterpret_cast<char*>(reason));
			staff_transfer.setNumber(reinterpret_cast<char*>(number));
			std::string str = reinterpret_cast<char*>(order_date);
			staff_transfer.setDate(staff_transfer.setStringDate(str));

			Storage::getInstance()->putStaffTransfer(staff_transfer);
			staff_transfer_vector.push_back(Storage::getInstance()->getStaffTransfer(staff_transfer.getId()));
		}
		else {
			if (retcode != SQL_NO_DATA) {
				std::cout << "Error fetching genres\n";
			}
			break;
		}
	}
	SQLFreeStmt(statement, SQL_CLOSE);
	return staff_transfer_vector;
}
