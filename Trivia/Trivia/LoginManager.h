#pragma once

#include <memory>
#include <vector>
#include "SqliteDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	// ctor and dtor
	LoginManager();
	~LoginManager() = default;

	// db methods
	void logout(const std::string& username);
	void login(const std::string& username, const std::string& password);
	void signup(const std::string username, 
		const std::string password, const std::string mail);

private:
	std::shared_ptr<IDatabase> m_database;
	std::vector<LoggedUser> m_loggedUsers;

	// Error functions
	void printDoesntExistError(const std::string& username) const;
	void printPasswordDoesntMatchError(const std::string & username,
		const std::string& password) const;
};	

