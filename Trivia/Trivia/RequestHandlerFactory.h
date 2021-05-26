#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"

class LoginManager;
class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(LoginManager loginManager);

	RequestHandlerFactory(IDatabase* database);

	RequestHandlerFactory(LoginManager loginManager, IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();

	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database; 
};

