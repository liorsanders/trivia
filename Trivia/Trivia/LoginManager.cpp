#include "LoginManager.h"
#include <algorithm>
#include <iostream>

LoginManager::LoginManager()
{
	m_database = std::make_shared<SqliteDatabase>();
}

void LoginManager::logout(const std::string& username)
{
	std::remove(m_loggedUsers.begin(),
		m_loggedUsers.end(),
		username);
}

void LoginManager::login(const std::string& username,
	const std::string& password)
{
	if (m_database->doesUserExist(username))
	{
		if (m_database->doesPasswordMatch(username, password))
		{
			m_loggedUsers.emplace_back(username);
		}
		else
		{
			std::cerr << "Error: " << username << " and " << password <<
				" does not match." << std::endl;
		}
	}
	else
	{
		std::cerr << "Error: " << username << " does not exist." << std::endl;
	}
}




