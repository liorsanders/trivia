#include "LoginRequestHandler.h"
#include "Codes.h"
#include "LoginResponse.h"
#include "JsonResponsePacketSerializer.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request)
{
    return request.id == (int)Codes::Login;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request)
{
    RequestResult result = RequestResult();
    LoginResponse response = LoginResponse();

    response.status = 1;

    result.response =
        JsonResponsePacketSerializer::serializeResponse(response);
    result.newHandler = nullptr;

    return result;
}

