#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

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
        return RequestResult();

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