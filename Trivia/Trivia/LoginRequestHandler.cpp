#include "LoginRequestHandler.h"
#include "Codes.h"
#include "LoginResponse.h"
#include "JsonResponsePacketSerializer.h"

RequestResult LoginRequestHandler::login(RequestInfo info)
{
    return handleRequest(info);
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
    return RequestResult();
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request)
{
    return request.id == (int)Codes::Login || request.id == (int)Codes::Signup;
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

