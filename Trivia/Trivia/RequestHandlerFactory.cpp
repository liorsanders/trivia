#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(LoginManager loginManager) :
    m_loginManager(loginManager), m_database(nullptr)
{
}

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
    m_database(database), m_loginManager(database)
{
}

RequestHandlerFactory::RequestHandlerFactory(LoginManager loginManager,
    IDatabase* database) :
    m_loginManager(loginManager), m_database(database) 
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* res = new LoginRequestHandler(this->m_loginManager, *this);
    return res;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
    MenuRequestHandler* newMenuRequestHandler = new MenuRequestHandler("", m_roomManager, m_statisticsManager, *this);;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_statisticsManager;
}
