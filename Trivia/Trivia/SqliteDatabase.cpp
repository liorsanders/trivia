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
		"id	INTEGER,"
		"name TEXT NOT NULL,"
		"password TEXT NOT NULL,"
		"mail TEXT NOT NULL,"
		"PRIMARY KEY(id AUTOINCREMENT)"
		");";

	int isBad = sqlite3_exec(db,
		sql.c_str(),
		NULL,
		NULL,
		&errorMessage);

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
	std::string sql = "SELECT id FROM users WHERE name like '" + username + "';";
	
	int isBad = sqlite3_exec(db,
		sql.c_str(),
		SqliteDatabase::doeasExistsCallback,
		&isExist,
		&errorMessage);

	if (isBad != SQLITE_OK)
	{
		std::cerr << "Error: " << errorMessage << std::endl;
	}

	return isExist;
}

bool SqliteDatabase::doesPasswordMatch 
	(std::string username, std::string password) const
{
	bool isExist = false;
	char* errorMessage;
	std::string sql = "SELECT id FROM users WHERE "
		"name LIKE '" + username +
		"' AND password LIKE '" + password + "';";

	int isBad = sqlite3_exec(db,
		sql.c_str(),
		SqliteDatabase::doeasExistsCallback,
		&isExist,
		&errorMessage);

	if (isBad != SQLITE_OK)
	{
		std::cerr << "Error: " << errorMessage << std::endl;
	}

	return isExist;
}

int SqliteDatabase::doeasExistsCallback
	(void* isExists, int argc, char ** argv, char ** cols)
{
	*(bool*)isExists = argc > 0;

	return 0;
}

void SqliteDatabase::addNewUser
	(std::string username, std::string password, std::string mail)
{
	char* errorMessage;
	std::string sql = "INSERT INTO users"
		"(name, password, mail)"
		"VALUES('" + username + "', '" + password + "', '" + mail + "');";

	int isBad = sqlite3_exec(db,
		sql.c_str(),
		NULL,
		NULL,
		&errorMessage);

	if (isBad != SQLITE_OK)
	{
		std::cerr << "Error: " << errorMessage << std::endl;
	}
}
