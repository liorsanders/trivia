#include "RoomAdminRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (int)Codes::CloseRoom == info.id ||
		(int)Codes::Start == info.id ||
		(int)Codes::GetRoomState == info.id;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
    switch (info.id)
    {
    case (int)Codes::GetRoomState:
        return RequestResult();

    case (int)Codes::LeaveRoom:
        return RequestResult();

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


RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo)
{
    GetRoomsResponse response = { 1, m_roomManager.getRooms() };

    RequestResult result = { JsonResponsePacketSerializer::serializeResponse(response),
                             this };

    return result;
}
