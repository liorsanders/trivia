#include "SqliteDatabase.h"
#include <iostream>

SqliteDatabase::SqliteDatabase()
{
	createDB();
	createTable();
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(db);
}

void SqliteDatabase::createTable()
{
	char* errorMessage;
	std::string sql = "CREATE TABLE IF NOT EXISTS users("
		"ID	INTEGER,"
		"Name TEXT NOT NULL,"
		"Password TEXT NOT NULL,"
		"Mail TEXT NOT NULL,"
		"PRIMARY KEY(ID AUTOINCREMENT)"
		");";

	int isBad = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errorMessage);

	if (isBad != SQLITE_OK)
	{
		std::cerr << "Can't open database: " << errorMessage << std::endl;
	}

}

void SqliteDatabase::createDB()
{
	int isBad = sqlite3_open("Trivia.db", &db);

	if (isBad != SQLITE_OK)
	{
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
	}
	else 
	{
		std::cout << "Opened database successfully!" << std::endl;
	}
}

bool SqliteDatabase::doesUserExist(std::string username) const
{
	bool isExist = false;
	char* errorMessage;
	std::string sql = "SELECT ID WHERE Name like " + username + ";";
	
	int isBad = sqlite3_exec(db,
		sql.c_str(),
		SqliteDatabase::doesUserExistCallback,
		&isExist,
		&errorMessage);

	if (isBad != SQLITE_OK)
	{
		std::cerr << "Error: " << errorMessage << std::endl;
	}

	return isExist;
}

int SqliteDatabase::doesUserExistCallback
	(void* isExists, int argc, char ** argv, char ** cols)
{
	*(bool*)isExists = argc > 0;

	return 0;
}

bool SqliteDatabase::doesPasswordMatch const
	(std::string username, std::string password)
{
	return false;
}

void SqliteDatabase::addNewUser
	(std::string username, std::string password, std::string mail)
{
}
