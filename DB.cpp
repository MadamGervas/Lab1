#include "DB.h"

void DB::connect()
{
	SQLWCHAR name[] = L"PostgreSQL30";
	SQLWCHAR user_name[] = L"admin";
	SQLWCHAR pass[] = L"123";
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &environment) == SQL_ERROR)
	{
		fwprintf(stderr, L"Unable to allocate an environment handle\n");
		exit(-1);
	}

	if (SQLSetEnvAttr(environment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) == SQL_ERROR) {
		fwprintf(stderr, L"Unable to set an environment variable\n");
		exit(-1);
	}

	if (SQLAllocHandle(SQL_HANDLE_DBC, environment, &connection) == SQL_ERROR) {
		fwprintf(stderr, L"Unable to allocate an connection handle\n");
		exit(-1);
	}

	if (SQLConnect(connection, name, SQL_NTS, user_name, SQL_NTS, pass, SQL_NTS) == SQL_ERROR) {
		fwprintf(stderr, L"Unable to connect\n");
		exit(-1);
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, connection, &statement) == SQL_ERROR) {
		fwprintf(stderr, L"Unable to allocate stmt handle\n");
		exit(-1);
	}
}

DB::DB() {
	connect();
}

DB::~DB()
{
	if (this->statement != SQL_NULL_HSTMT)
		SQLFreeHandle(SQL_HANDLE_STMT, this->statement);

	if (this->connection != SQL_NULL_HDBC) {
		SQLDisconnect(this->connection);
		SQLFreeHandle(SQL_HANDLE_DBC, this->connection);
	}

	if (this->environment != SQL_NULL_HENV)
		SQLFreeHandle(SQL_HANDLE_ENV, this->environment);
}


const wchar_t* DB::getWChar(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);
	return wc;
}

const SQLHSTMT& DB::execute(const char* sql)
{
	SQLRETURN ret = SQLExecDirect(statement,
		(SQLWCHAR*)getWChar(sql), SQL_NTS);
	if (ret == SQL_SUCCESS) {
		return this->statement;
	}
	/*if (ret == SQL_SUCCESS_WITH_INFO) cout << "SQL_SUCCESS_WITH_INFO" << endl;
	else if (ret == SQL_NEED_DATA) cout << "SQL_NEED_DATA" << endl;
	else if (ret == SQL_STILL_EXECUTING) cout << "SQL_STILL_EXECUTING" << endl;
	else if (ret == SQL_ERROR) cout << "SQL_ERROR" << endl;
	else if (ret == SQL_NO_DATA) cout << "SQL_NO_DATA" << endl;
	else if (ret == SQL_INVALID_HANDLE) cout << "SQL_INVALID_HANDLE" << endl;
	else cout << "return value not found" << endl;*/

	return nullptr;
}