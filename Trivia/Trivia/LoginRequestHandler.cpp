#include "LoginRequestHandler.h"
#include "Codes.h"
#include "LoginResponse.h"
#include "JsonResponsePacketSerializer.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request)
{
    return request.id == (int)Codes::Login ||
        request.id == (int)Codes::Signup;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request)
{
    switch (request.id)
    {
    case (int)Codes::Login:
        return createRequestResult(LoginResponse());

    case (int)Codes::Signup:
        return createRequestResult(SignupResponse());

    default:
        std::cout << "Error: Unknown message code. " << std::endl;
        return createRequestResult(ErrorResponse());
    }
}

RequestResult LoginRequestHandler::createRequestResult(LoginResponse response)
{
    RequestResult result = RequestResult();
    response.status = 1;

    result.response =
        JsonResponsePacketSerializer::serializeResponse(response);

    result.newHandler = nullptr;

    return result;
}

RequestResult LoginRequestHandler::createRequestResult(SignupResponse response)
{
    RequestResult result = RequestResult();
    response.status = 1;

    result.response =
        JsonResponsePacketSerializer::serializeResponse(response);

    result.newHandler = new LoginRequestHandler();
    
    return result;
}

RequestResult LoginRequestHandler::createRequestResult(ErrorResponse response)
{
    RequestResult result = RequestResult();

    response.message = "Unknown message code";
    result.response =
        JsonResponsePacketSerializer::serializeResponse(response);

    result.newHandler = nullptr;

    return result; 
}
