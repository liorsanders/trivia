#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(const std::string username, RoomManager& roomManager,
    StatisticsManager& statisticsManager, RequestHandlerFactory& factory) : m_user(LoggedUser(username)),
    m_statisticsManager(statisticsManager), m_handlerFactory(factory), m_roomManager(roomManager) {}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
    return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& request)
{
    return RequestResult();
}
