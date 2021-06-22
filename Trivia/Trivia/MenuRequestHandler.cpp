#include "MenuRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>

MenuRequestHandler::MenuRequestHandler(const std::string username, RoomManager& roomManager,
    StatisticsManager& statisticsManager, RequestHandlerFactory& factory) : m_user(LoggedUser(username)),
    m_statisticsManager(statisticsManager), m_handlerFactory(factory), m_roomManager(roomManager) {}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
    int code = request.id;
    return int(Codes::CreateRoom) == code ||
        int(Codes::GetPlayers) == code ||
        int(Codes::GetRoom) == code ||
        int(Codes::JoinRoom) == code ||
        int(Codes::Logout) == code ||
        int(Codes::Statistics) == code;
}

RequestResult createError(MenuRequestHandler* menu) {
    std::string error = "invalid message code";
    RequestResult result = RequestResult();
    std::cout << error << std::endl;
    result.newHandler = menu;
    ErrorResponse errorResponse = { error };
    result.response =
        JsonResponsePacketSerializer::serializeResponse(errorResponse);
    return result;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& request)
{
    RequestResult requestResult;
    switch (request.id) {
    case (int)Codes::CreateRoom:
        return createRoom(request);
    case (int)Codes::GetPlayers:
        return getPlayersInRoom(request);
    case (int)Codes::GetRoom:
        return getRooms(request);
    case (int)Codes::JoinRoom:
        return joinRoom(request);
    case (int)Codes::Logout:
        return signout(request);
    case (int)Codes::Statistics:
        return getHighScore(request);
    }
    return createError(this);
}

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
    RequestResult requestResult;
    requestResult.newHandler = nullptr;
    return requestResult;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
    RequestResult requestResult;
    GetRoomsResponse response;
    response.rooms = m_roomManager.getRooms();
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    requestResult.newHandler = this;
    return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
    auto request = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
    int state = m_roomManager.getRoomState(request.roomId);
    RequestResult requestResult;
    GetPlayersInRoomResponse response;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    requestResult.newHandler = this;
    return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
    //implement in v3
    return RequestResult();
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
    //implement in v3
    return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
    //implement in v3
    RequestResult requestResult;
    auto request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
    requestResult.newHandler = this;
    JoinRoomResponse response;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    return requestResult;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
    RequestResult requestResult;
    auto deserialized = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
    try {
        RoomData data;
        data.isActive = true;
        data.name = deserialized.roomName;
        m_roomManager.createRoom(m_user, data);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    CreateRoomResponse response;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    requestResult.newHandler = this;
    return requestResult;
}
