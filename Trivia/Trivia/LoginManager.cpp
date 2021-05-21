#include "LoginManager.h"
#include <algorithm>

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

