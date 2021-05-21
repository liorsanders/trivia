#include "LoginManager.h"
#include <algorithm>
#include <iostream>

LoginManager::LoginManager()
{
	m_database = std::make_shared<SqliteDatabase>();
}

void LoginManager::logout(std::string username)
{
	std::remove(m_loggedUsers.begin(),
		m_loggedUsers.end(),
		username);
}

void LoginManager::login(std::string username, std::string password)
{
	m_database->doesUserExist(username) ?

		m_database->doesPasswordMatch(username, password) ?
			m_loggedUsers.emplace_back(username)
			:
			printPasswordDoesntMatchError(username, password)
		:
		printDoesntExistError(username);
}

void LoginManager::printDoesntExistError(const std::string& username) const
{
	std::cout << "Error: " << username << " does not exist." << std::endl;

}

void LoginManager::printPasswordDoesntMatchError
	(const std::string & username, const std::string& password) const
{
	std::cout << "Error: " << username << " and " << password <<
		" does not match." << std::endl;
}

