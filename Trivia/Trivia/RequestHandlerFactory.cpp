#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(LoginManager loginManager) :
    m_loginManager(loginManager), m_database(nullptr)
{
    m_statisticsManager = StatisticsManager();
}

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
    m_database(database), m_loginManager(database)
{
    m_statisticsManager = StatisticsManager();

}

RequestHandlerFactory::RequestHandlerFactory(LoginManager loginManager,
    IDatabase* database) :
    m_loginManager(loginManager), m_database(database) 
{
    m_statisticsManager = StatisticsManager();
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

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(
    Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory)
{
    return new RoomAdminRequestHandler(room, user, roomManager, handlerFactory);
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
