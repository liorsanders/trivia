#include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "Communicator.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user,
    RoomManager& roomManager, RequestHandlerFactory& handlerFactory) :
    m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& info) const
{
	return (int)Codes::CloseRoom == info.id ||
		(int)Codes::Start == info.id ||
		(int)Codes::GetRoomState == info.id;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& info)
{
    switch (info.id)
    {
    case (int)Codes::Start:
        return RequestResult();

    case (int)Codes::GetRoomState:
        return getRoomState(info);

    case (int)Codes::CloseRoom:
        return closeRoom(info);

    default:
        std::string error = "inavlid message code";
        RequestResult result = RequestResult();

        return createErrorResponse(error, result);
    }
}

const RequestResult& RoomAdminRequestHandler::createErrorResponse
    (const std::string& error, RequestResult& result)
{
    std::cout << error << std::endl;

    result.newHandler = this;

    ErrorResponse errorResponse = { error };

    result.response =
        JsonResponsePacketSerializer::serializeResponse(errorResponse);

    return result;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
    int id = m_room.getRoomData().id;
    m_roomManager.deleteRoom(id);
    
    LeaveRoomRequest request = { };

    StatisticsManager stats;

    RequestResult result = { JsonResponsePacketSerializer::serializeResponse(request),
                             new MenuRequestHandler(m_user, m_roomManager, stats, m_handlerFactory) };

    auto users = m_roomManager.getLoggedUser(id);

    for (auto& user : users)
    {
        SOCKET sock = user.getSocket();

        LeaveRoomRequest request = { };

        auto message = JsonResponsePacketSerializer::serializeResponse(request);

        Communicator::sendMessage(sock, message);
    }

    return result;
}


RequestResult RoomAdminRequestHandler::startGame(RequestInfo)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo)
{
    GetRoomsResponse response = { 1, m_roomManager.getRooms() };

    RequestResult result = { JsonResponsePacketSerializer::serializeResponse(response),
                             this };

    return result;
}
