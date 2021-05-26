#include "LoginManager.h"
#include "InvalidLoginException.h"
#include <algorithm>
#include <iostream>

LoginManager::LoginManager()
{
	m_database = std::make_shared<SqliteDatabase>();
}

void LoginManager::logout(std::string username)
{
	auto loggedUser = std::find(m_loggedUsers.begin(),
		m_loggedUsers.end(),
		LoggedUser(username));

	if (loggedUser == m_loggedUsers.end())
	{
		std::cerr << "Error: can not logout " << username
			<< " because user is not online." << std::endl;
		return;
	}

	m_loggedUsers.erase(loggedUser);
}

void LoginManager::login(std::string username,
	std::string password)
{
	if (!m_database->doesUserExist(username))
	{
		std::cerr << "Error: " << username << " does not exist." << std::endl;
		
		throw InvalidLoginException("user does not exist");
	}

	if (!m_database->doesPasswordMatch(username, password))
	{
		std::cerr << "Error: " << username << " and " << password <<
			" does not match." << std::endl;
		throw InvalidLoginException("invalid username or password");
	}

	m_loggedUsers.emplace_back(username);
}

void LoginManager::signup(const std::string username,
	const std::string password, const std::string mail)
{
	if (m_database->doesUserExist(username))
	{
		std::cerr << "Error: " << username << "is already exist." << std::endl;
		throw InvalidLoginException("user already exists");
	}

	m_database->addNewUser(username, password, mail);

}

