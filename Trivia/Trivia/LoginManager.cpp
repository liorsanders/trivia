#include "LoginManager.h"
#include "InvalidLoginException.h"
#include <algorithm>
#include <iostream>
#include <WinSock2.h>

LoginManager::LoginManager(IDatabase* db) :
	m_database(db)
{
}

void LoginManager::logout(const std::string& username)
{
	SOCKET sock = 0;
	auto loggedUser = std::find(m_loggedUsers.begin(),
		m_loggedUsers.end(),
		LoggedUser(username, sock));

	if (loggedUser == m_loggedUsers.end())
	{
		std::cerr << "Error: can not logout " << username
			<< " because user is not online." << std::endl;
		return;
	}

	std::lock_guard<std::mutex> lock(m_loggedUsersMutex);
	m_loggedUsers.erase(loggedUser);
}

LoggedUser LoginManager::login(const std::string& username,
	const std::string& password, SOCKET& sock)
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

	std::lock_guard<std::mutex> lock(m_loggedUsersMutex);
	m_loggedUsers.emplace_back(username, sock);
	
	return m_loggedUsers.back();
}

LoggedUser LoginManager::signup(const std::string username,
	const std::string password, const std::string mail, SOCKET& sock)
{
	if (m_database->doesUserExist(username))
	{
		std::cerr << "Error: " << username << "is already exist." << std::endl;
		throw InvalidLoginException("user already exists");
	}
	std::unique_lock<std::mutex> dbLock(m_databaseMutex);
	m_database->addNewUser(username, password, mail);
	dbLock.unlock();

	std::lock_guard<std::mutex> userLock(m_loggedUsersMutex);
	m_loggedUsers.emplace_back(username, sock);

	return m_loggedUsers.back();
}