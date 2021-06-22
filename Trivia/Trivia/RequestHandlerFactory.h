#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"

class LoginManager;
class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(LoginManager loginManager);

	RequestHandlerFactory(IDatabase* database);

	RequestHandlerFactory(LoginManager loginManager, IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler(SOCKET& sock);
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	
	RoomManager& getRoomManager();
	LoginManager& getLoginManager();
	StatisticsManager& getStatisticsManager();

private:
	StatisticsManager m_statisticsManager;
	RoomManager m_roomManager;
	LoginManager m_loginManager;
	IDatabase* m_database; 
};

