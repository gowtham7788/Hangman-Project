#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include "Property.h"
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

using namespace std;

class DatabaseConnection
{
private:
	SQLHANDLE SqlHandle;
	SQLHANDLE SqlConnHandle;
	SQLHANDLE SqlEnvHandle;
	SQLWCHAR RetConString[SQL_RETURN_CODE_LEN];
public:
	DatabaseConnection();
	~DatabaseConnection();
	SQLHANDLE get_connection_handler();
};

