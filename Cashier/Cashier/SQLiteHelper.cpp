#include <iostream>
#include "SQLiteHelper.h"

using namespace std;

SQLiteHelper::SQLiteHelper()
{
}

SQLiteHelper::~SQLiteHelper()
{
}

int SQLiteHelper::execSQL(const char *sql)
{
	return sqlite3_exec(db, sql, 0, 0, 0);
}

int SQLiteHelper::rawQuery(const char *sql, int *row, int *column, char **result)
{
	//return sqlite3_get_table(db, sql, &result, row, column, 0);
	return 0;
}

int SQLiteHelper::openDB(char *path)
{
	return sqlite3_open(path, &db);
}

sqlite_int64 SQLiteHelper::getLastID()
{
	return sqlite3_last_insert_rowid(db);
}

void SQLiteHelper::closeDB()
{
	sqlite3_close(db);
}