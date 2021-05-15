#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase() override;

	bool doesUserExist(std::string username) const override;

	bool doesPasswordMatch
		(std::string username, std::string password) const override;

	void addNewUser
			(std::string username, std::string password, std::string mail) override;
private:
	sqlite3* db;

	void createTable();
	void createDB();
	static int doeasExistsCallback
		(void* isExists, int argc, char** argv, char** cols);

};

