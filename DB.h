#pragma once
#ifndef DB_HEADER
#define DB_HEADER
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "windows.h"
#include <sql.h>
#include <sqlext.h>
#include <string>

using namespace std;
class DB {

private:
    SQLHENV environment;
    SQLHDBC connection;
    SQLHSTMT statement;

private:
    void connect();

public:

    DB();
    ~DB();

    const SQLHSTMT& execute(const char* sql);
    const wchar_t* getWChar(const char* sql);

};
#endif