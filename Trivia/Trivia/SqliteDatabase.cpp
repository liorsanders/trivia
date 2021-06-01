#include "SqliteDatabase.h"
#include "StatisticsInfo.h"
#include <iostream>

StatisticsInfo info;

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
	std::string createUserTable = "CREATE TABLE IF NOT EXISTS users("
		"id	INTEGER,"
		"name TEXT NOT NULL,"
		"password TEXT NOT NULL,"
		"mail TEXT NOT NULL,"
		"PRIMARY KEY(id AUTOINCREMENT)"
		");";

	std::string createStatisticsTable = "CREATE TABLE IF NOT EXISTS statistics (num_correct_answers INTEGER NOT NULL,num_wrong_answers INTEGER NOT NULL,num_games INTEGER NOT NULL,total_time FLOAT NOT NULL,user_id INTEGER,FOREIGN KEY(user_id) REFERENCES users(id));";

	int isBad = sqlite3_exec(db,
		createUserTable.c_str(),
		NULL,
		NULL,
		&errorMessage);

	if (isBad != SQLITE_OK)
	{
		std::cerr << "Can't open database: " << errorMessage << std::endl;
	}

	isBad = sqlite3_exec(db,
		createStatisticsTable.c_str(),
		NULL,
		NULL,
		&errorMessage);

	if (isBad != SQLITE_OK) {
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

bool SqliteDatabase::doesUserExist(const std::string& username) const
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
(const std::string& username, const std::string& password) const
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
(void* isExists, int argc, char** argv, char** cols)
{
	*(bool*)isExists = argc > 0;

	return 0;
}

int SqliteDatabase::statisticsCallBack(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		if (azColName[i] == std::string("num_correct_answers")) {
			info.correctCount = std::stoi(argv[i]);
		}
		else if (azColName[i] == std::string("num_wrong_answers")) {
			info.incorrectCount = std::stoi(argv[i]);
		}
		else if (azColName[i] == std::string("num_games")) {
			info.totalGames = std::stoi(argv[i]);
		}
		else if (azColName[i] == std::string("total_time")) {
			info.totalTime = std::stof(argv[i]);
		}
	}
}

void SqliteDatabase::addNewUser
(const std::string& username, const std::string& password, const std::string& mail)
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

float SqliteDatabase::getPlayersAverageAnswerTime(const std::string& username) const
{
	bool flag = false;
	char* errorMessage;
	std::string sql = "SELECT num_correct_answers, num_wrong_answers, num_games, total_time, FROM users WHERE "
		"name LIKE '" + username + ";";
	int isBad = sqlite3_exec(db,
		sql.c_str(),
		&SqliteDatabase::statisticsCallBack,
		&flag,
		&errorMessage
	);
	if (isBad != SQLITE_OK) {
		std::cerr << errorMessage << std::endl;
	}
	if (info.correctCount + info.incorrectCount == 0) {
		return 0;
	}
	return info.totalTime / (info.correctCount + info.incorrectCount);
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string& username) const
{
	bool flag = false;
	char* errorMessage;
	std::string sql = "SELECT num_correct_answers FROM users WHERE "
		"name LIKE '" + username + ";";
	int isBad = sqlite3_exec(db,
		sql.c_str(),
		&SqliteDatabase::statisticsCallBack,
		&flag,
		&errorMessage
	);
	if (isBad != SQLITE_OK) {
		std::cerr << errorMessage << std::endl;
	}
	return info.correctCount;
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string& username) const
{
	bool flag = false;
	char* errorMessage;
	std::string sql = "SELECT num_correct_answers FROM users WHERE "
		"name LIKE '" + username + ";";
	int isBad = sqlite3_exec(db,
		sql.c_str(),
		&SqliteDatabase::statisticsCallBack,
		&flag,
		&errorMessage
	);
	if (isBad != SQLITE_OK) {
		std::cerr << errorMessage << std::endl;
	}
	return info.correctCount + info.incorrectCount;
}

int SqliteDatabase::getNumOfPlayerGames(const std::string& username) const
{
	bool flag = false;
	char* errorMessage;
	std::string sql = "SELECT num_correct_answers FROM users WHERE "
		"name LIKE '" + username + ";";
	int isBad = sqlite3_exec(db,
		sql.c_str(),
		&SqliteDatabase::statisticsCallBack,
		&flag,
		&errorMessage
	);
	if (isBad != SQLITE_OK) {
		std::cerr << errorMessage << std::endl;
	}
	return info.totalGames;
}
