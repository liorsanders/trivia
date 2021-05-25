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
        return HandleLoginRequest(request);

    case (int)Codes::Signup:
        return HandleSignupRequest(request);

    default:
        return HandleErrorRequest(request);
    }
}

RequestResult LoginRequestHandler::HandleLoginRequest(const RequestInfo& request)
{
    RequestResult result = RequestResult();
    LoginResponse response = { 1 }; // init status with 1 that equal to true

    result.response =
        JsonResponsePacketSerializer::serializeResponse(response);

    result.newHandler = nullptr;

    return result;
}

RequestResult LoginRequestHandler::HandleSignupRequest(const RequestInfo& request)
{
    RequestResult result = RequestResult();
    SignupResponse response = { 1 }; // init status with 1 that equal to true

    result.response =
        JsonResponsePacketSerializer::serializeResponse(response);

    result.newHandler = new LoginRequestHandler;
    
    return result;
}

RequestResult LoginRequestHandler::HandleErrorRequest(const RequestInfo& request)
{
    RequestResult result = RequestResult();
    ErrorResponse response = { "Unknown message code" };

    std::cerr << "Error: Unknown message code!." << std::endl;

    result.response =
        JsonResponsePacketSerializer::serializeResponse(response);

    result.newHandler = nullptr;

    return result; 
}
