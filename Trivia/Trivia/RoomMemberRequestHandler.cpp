#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"
#include <iostream>

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    return (int)Codes::GetRoomState == info.id ||
        (int)Codes::LeaveRoom == info.id;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
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

    RequestResult result = { JsonResponsePacketSerializer::serializeResponse(response),
                             new MenuRequestHandler };

    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo)
{
    GetRoomsResponse response = { 1, m_roomManager.getRooms() };

    RequestResult result = { JsonResponsePacketSerializer::serializeResponse(response),
                             this };

    return result;
}