#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"

class LoginManager;
class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory() {}
	RequestHandlerFactory(LoginManager loginManager) :
		m_loginManager(loginManager), m_database(nullptr) {}
	RequestHandlerFactory(IDatabase* database) :
		m_database(database) {}
	RequestHandlerFactory(LoginManager loginManager, IDatabase* database) :
		m_loginManager(loginManager), m_database(database) {}
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabase* m_database; 
};

