#include "LoginRequestHandler.h"
#include "Codes.h"
#include "LoginResponse.h"
#include "JsonResponsePacketSerializer.h"
#include "InvalidLoginException.h"
#include "MenuRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager,
    RequestHandlerFactory& handlerFactory):
    m_loginManager(loginManager), m_handlerFactory(handlerFactory) 
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
    return request.id == (int)Codes::Login || request.id == (int)Codes::Signup;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request) 
{
    switch (request.id)
    {
    case (int)Codes::Login:
        return login(request);

    case (int)Codes::Signup:
        return signup(request);

    default:
        std::string error = "inavlid message code";
        RequestResult result = RequestResult();

        return createErrorResponse(error, result);
    }
}

RequestResult LoginRequestHandler::login(RequestInfo info) 
{
    RequestResult result;

    auto request = 
        JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);

    try 
    {
        m_loginManager.login(request.username,
            request.password);
    }
    catch (const InvalidLoginException& e) 
    {
        return createErrorResponse(e.what(), result);
    }

    LoginResponse response = { (int)Codes::Login };

    result.response = JsonResponsePacketSerializer::serializeResponse(response);
    result.newHandler = new MenuRequestHandler();

    return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
    RequestResult result;
    auto signupRequest =
        JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);

    try
    {
        m_loginManager.signup(signupRequest.username,
            signupRequest.password,
            signupRequest.email);
    }
    catch (const InvalidLoginException& e)
    {
        return createErrorResponse(e.what(), result);
    }

    SignupResponse response = { int(Codes::Signup) };

    result.response = JsonResponsePacketSerializer::serializeResponse(response);
    result.newHandler = new MenuRequestHandler();

    return result;
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



