#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    return (int)Codes::Start == info.id ||
        (int)Codes::GetRoomState == info.id ||
        (int)Codes::LeaveRoom == info.id;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
    switch (info.id)
    {
    case (int)Codes::Start:
        return;

    case (int)Codes::GetRoomState:
        return;

    case (int)Codes::LeaveRoom:
        return;

    default:
        std::string error = "inavlid message code";
        RequestResult result = RequestResult();

        return createErrorResponse(error, result);
    }
}

const RequestResult& LoginRequestHandler::createErrorResponse
    (const std::string& error, RequestResult& result)
{
    std::cout << error << std::endl;

    result.newHandler = this;

    ErrorResponse errorResponse = { error };

    result.response =
        JsonResponsePacketSerializer::serializeResponse(errorResponse);

    return result;
}