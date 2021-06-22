#pragma once

#include <string>
#include <map>

class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool doesUserExist(const std::string& username) const = 0;

	virtual bool doesPasswordMatch(const std::string& username,
		const std::string& password) const = 0;

	virtual void addNewUser(const std::string& username,
		const std::string& password, const std::string& mail) = 0;

	virtual std::map<std::string, float> getUsersScores() const = 0;
	virtual float getPlayersAverageAnswerTime(const std::string& username) const = 0;
	virtual int getNumOfCorrectAnswers(const std::string& username) const = 0;
	virtual int getNumOfTotalAnswers(const std::string& username) const = 0;
	virtual int getNumOfPlayerGames(const std::string& username) const = 0;

};
