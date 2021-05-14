#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDatabase /*: IDatabase*/
{
public:
	SqliteDatabase();
	~SqliteDatabase();

	virtual bool doesUserExist(std::string username) const;

	virtual bool doesPasswordMatch
		(std::string username, std::string password) const;

	virtual void addNewUser
		(std::string username, std::string password, std::string mail);

private:
	sqlite3* db;

	void createTable();
	void createDB();
	static int doeasExistsCallback
	(void* isExists, int argc, char ** argv, char ** cols);

};

