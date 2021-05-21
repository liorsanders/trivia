#pragma once

#include <memory>
#include <vector>
#include "SqliteDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager();
	~LoginManager() = default;

	void logout(std::string username);
	void login(std::string username, std::string password);
	void signup(std::string username, std::string password, std::string mail);

private:
	std::shared_ptr<IDatabase> m_database;
	std::vector<LoggedUser> m_loggedUsers;

	void printDoesntExistError(const std::string& username) const;
	void printPasswordDoesntMatchError(const std::string & username, const std::string& password) const;
};	

