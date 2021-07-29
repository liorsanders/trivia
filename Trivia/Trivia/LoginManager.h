#pragma once

#include <vector>
#include "SqliteDatabase.h"
#include "LoggedUser.h"
#include <mutex>

class LoginManager
{
public:
	// ctor and dtor
	LoginManager() {}
	LoginManager(IDatabase* db);
	LoginManager(const LoginManager& other) {
		m_database = other.m_database;
		m_loggedUsers = other.m_loggedUsers;
	}
	~LoginManager() = default;

	// db methods
	void logout(const std::string& username);
	LoggedUser login(const std::string& username, const std::string& password, SOCKET& sock);
	LoggedUser signup(const std::string username,
		const std::string password, const std::string mail, SOCKET& sock);

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
	std::mutex m_databaseMutex;
	std::mutex m_loggedUsersMutex;

};	

