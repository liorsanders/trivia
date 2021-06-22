#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include <iostream>

RoomMemberRequestHandler::RoomMemberRequestHandler(Room room, LoggedUser user,
    RoomManager& roomManager, RequestHandlerFactory& handlerFactory) :
    m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}


bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& info) const
{
    return (int)Codes::GetRoomState == info.id ||
        (int)Codes::LeaveRoom == info.id;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& info) 
{
    switch (info.id)
    {
    case (int)Codes::GetRoomState:
        return getRoomState(info);

    case (int)Codes::LeaveRoom:
        return leaveRoom(info);

    default:
        std::string error = "inavlid message code";
        RequestResult result = RequestResult();

        return createErrorResponse(error, result);
    }
}

const RequestResult& RoomMemberRequestHandler::createErrorResponse
    (const std::string& error, RequestResult& result)
{
    std::cout << error << std::endl;

    result.newHandler = this;

    ErrorResponse errorResponse = { error };

    result.response =
        JsonResponsePacketSerializer::serializeResponse(errorResponse);

    return result;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
    try
    {
        m_room.removeUser(m_user);
    }
    catch (...)
    {
        std::cerr << "Error while removing user..." << std::endl;
    }

    LeaveRoomResponse response = { 1 };

    StatisticsManager stats = StatisticsManager();
    RequestResult result = { JsonResponsePacketSerializer::serializeResponse(response),
                             new MenuRequestHandler(m_user,
                                 m_roomManager,
                                 stats,
                                 m_handlerFactory) };

    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo)
{
    GetRoomsResponse response = { 1, m_roomManager.getRooms() };

    RequestResult result = { JsonResponsePacketSerializer::serializeResponse(response),
                             this };

    return result;
}
