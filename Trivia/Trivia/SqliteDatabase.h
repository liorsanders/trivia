#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <memory>

class SqliteDatabase : IDatabase
{
public:
	SqliteDatabase();
	void createDB();
	~SqliteDatabase();
	virtual bool doesUserExist(std::string username);
	virtual bool doesPasswordMatch(std::string username, std::string password);
	virtual void addNewUser(std::string username, std::string password, std::string mail);

private:
	std::shared_ptr<sqlite3> DB;
};

