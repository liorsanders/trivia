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

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler(SOCKET& sock)
{
    LoginRequestHandler* res = new LoginRequestHandler(this->m_loginManager, *this, sock);
    return res;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(user, m_roomManager, m_statisticsManager, *this);
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
