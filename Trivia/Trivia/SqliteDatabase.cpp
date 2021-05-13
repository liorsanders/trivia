#include "SqliteDatabase.h"
#include <iostream>

SqliteDatabase::SqliteDatabase()
{
	createDB();
	createTable();
}

void SqliteDatabase::createTable()
{
	std::string sql = "CREATE TABLE users("
		"ID	INTEGER,"
		"Name TEXT NOT NULL,"
		"Password TEXT NOT NULL,"
		"Mail TEXT NOT NULL,"
		"PRIMARY KEY(ID AUTOINCREMENT)"
		");";

	int isBad = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}

void SqliteDatabase::createDB()
{
	int isBad = sqlite3_open("users.db", &db);

	if (isBad)
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
	}
	else 
	{
		std::cerr << "Opened database successfully!" << std::endl;
	}
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(db);
}
