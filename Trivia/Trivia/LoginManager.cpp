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
	doesUserExist(username);
}

bool LoginManager::doesUserExist(std::string& username)
{
	if (!m_database->doesUserExist(username))
	{
		std::cout << "Error: " << username << " does not exists." << std::endl;

		return false;
	}

	return true;
}

