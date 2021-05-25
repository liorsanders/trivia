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
        return handleRequest(LoginResponse(), nullptr);
    case (int)Codes::Signup:
        return handleRequest(SignupResponse(), LoginRequestHandler());
    default:
        std::cout << "Error: Unknown message code. " << std::endl;
        return handleRequest(ErrorResponse(), nullptr);
    }
}

