#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase() override;

	bool doesUserExist(const std::string& username) const override;

	bool doesPasswordMatch(const std::string& username,
		const std::string& password) const override;

	void addNewUser(const std::string& username, 
		const std::string& password, const std::string& mail) override;

	std::map<std::string, float> getUsersScores() const override;
	float getPlayersAverageAnswerTime(const std::string& username) const override;
	int getNumOfCorrectAnswers(const std::string& username) const override;
	int getNumOfTotalAnswers(const std::string& username) const override;
	int getNumOfPlayerGames(const std::string& username) const override;

private:
	sqlite3* db;

	void createTable();
	void createDB();
	static int doeasExistsCallback
		(void* isExists, int argc, char** argv, char** cols);
	static int statisticsCallBack
	(void* data, int argc, char** argv, char** azColName);
	static int idAndNameCallback(void* data, int argc, char** argv, char** azColName);
	static int nameAndScoreCallback(void* data, int argc, char** argv, char** azColName);
};

