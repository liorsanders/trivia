#pragma once

#include <memory>
#include <vector>
#include "SqliteDatabase.h"
#include "LoggedUser.h"

class LoginManger
{
public:
	void signup(std::string username, std::string password, std::string mail);
	void login(std::string username, std::string password);
	void logout(std::string password);
private:
	std::shared_ptr<IDatabase> m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
