#pragma once
#include "IDatabase.h"
#include <winsqlite/winsqlite3.h>

class SqliteDatabase : IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	virtual bool doesUserExist(std::string username);
	virtual bool doesPasswordMatch(std::string username, std::string password);
	virtual void addNewUser(std::string username, std::string password, std::string mail);

private:
	sqlite3* db;
};

