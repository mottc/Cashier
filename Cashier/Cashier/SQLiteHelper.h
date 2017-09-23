#pragma once
#include "sqlite3.h"  
#include <windows.h>  
class SQLiteHelper
{

public:
	sqlite3 *db;

public:
	SQLiteHelper();
	virtual ~SQLiteHelper();
	int execSQL(const char *sql);
	int openDB(char *path);
	sqlite_int64 getLastID();
	void closeDB();
	char** rawQuery(const char *sql, int *row, int *column, char **result);
	
};