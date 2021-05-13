#include "SqliteDatabase.h"
#include <iostream>

SqliteDatabase::SqliteDatabase()
{
	DB = std::make_shared<sqlite3>();

	createDB();
}

void SqliteDatabase::createDB()
{
	sqlite3* rawDB = DB.get();

	int isBad = sqlite3_open("users.db", &rawDB);

	if (isBad)
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(rawDB) << std::endl;
	}
	else 
	{
		std::cerr << "Opened database successfully!" << std::endl;
	}

	delete rawDB;
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3* rawDB = DB.get();

	sqlite3_close(rawDB);

	delete rawDB;
}
