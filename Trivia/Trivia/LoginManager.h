#pragma once

#include <vector>
#include "SqliteDatabase.h"
#include "LoggedUser.h"
#include <mutex>

class LoginManager
{
public:
	// ctor and dtor
	LoginManager(IDatabase* db);
	LoginManager(const LoginManager& other) {
		m_database = other.m_database;
		m_loggedUsers = other.m_loggedUsers;
	}
	~LoginManager() = default;

	// db methods
	void logout(const std::string& username);
	void login(const std::string& username, const std::string& password);
	void signup(const std::string username, 
		const std::string password, const std::string mail);

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
	std::mutex m_databaseMutex;
	std::mutex m_loggedUsersMutex;

};	

