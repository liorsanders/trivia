#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager,
    StatisticsManager& statisticsManager, RequestHandlerFactory& factory) : m_user(user),
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
    case (int)Codes::HighScores:
        return getHighScore(request);
    case (int)Codes::PersonalStats:
        return getPersonalStats(request);
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
    auto users = m_roomManager.getLoggedUser(request.roomId);
    for (auto user : users) {
        response.players.push_back(user.getUsername());
    }
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    requestResult.newHandler = this;
    return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
    RequestResult requestResult;
    
    auto deserialized = JsonRequestPacketDeserializer::deserializePersonalStatsRequest(info.buffer);
    try {
        getPersonalStatsResponse response;
        response.statistics = m_statisticsManager.getUserStatistics(deserialized.username);
        requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return requestResult;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
    RequestResult request;

    try {
        auto highScores = m_statisticsManager.getHighScore();
        getHighScoreResponse response;
        for (int i = 0; i < highScores.size(); i++) {
            response.scores.push_back(highScores[i].second);
            response.usernames.push_back(highScores[i].first);
        }
        request.newHandler = this;
        request.response = JsonResponsePacketSerializer::serializeResponse(response);
        return request;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return request;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
    RequestResult requestResult;
    auto request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
    Room room;
    requestResult.newHandler = new RoomMemberRequestHandler(room, m_user, m_roomManager, m_handlerFactory);
    JoinRoomResponse response;
    response.status = 1;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    return requestResult;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
    RequestResult requestResult;
    auto deserialized = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
    RoomData data;
    try {
        data.isActive = true;
        data.name = deserialized.roomName;
        m_roomManager.createRoom(m_user, data);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    CreateRoomResponse response;
    Room room;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
    requestResult.newHandler = new RoomAdminRequestHandler(room, m_user, m_roomManager, m_handlerFactory);
    return requestResult;
}
