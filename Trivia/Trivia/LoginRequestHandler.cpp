#include "LoginRequestHandler.h"
#include "Codes.h"
#include "LoginResponse.h"
#include "JsonResponsePacketSerializer.h"
#include "InvalidLoginException.h"
#include "MenuRequestHandler.h"

RequestResult LoginRequestHandler::login(RequestInfo info) 
{
    RequestResult loginResult;
    auto loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    try {
        m_loginManager.login(loginRequest.username, loginRequest.password);
    }
    catch (const InvalidLoginException& e) {
        std::cout << e.what() << std::endl;
        loginResult.newHandler = this;
        ErrorResponse errorResponse;
        errorResponse.message = e.what();
        loginResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
        return loginResult;
    }

    LoginResponse resp;
    resp.status = (int)Codes::Login;
    loginResult.response = JsonResponsePacketSerializer::serializeResponse(resp);
    loginResult.newHandler = new MenuRequestHandler();
    return loginResult;
}

RequestResult LoginRequestHandler::signup(RequestInfo info) 
{
    RequestResult signupResult;
    auto signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    try {
        m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email);
    }
    catch (const InvalidLoginException& e) {
        std::cout << e.what() << std::endl;
        signupResult.newHandler = this;
        ErrorResponse errorResponse;
        errorResponse.message = e.what();
        signupResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
        return signupResult;
    }

    SignupResponse resp;
    resp.status = int(Codes::Signup);
    signupResult.response = JsonResponsePacketSerializer::serializeResponse(resp);
    signupResult.newHandler = new MenuRequestHandler();
    return signupResult;
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
    return request.id == (int)Codes::Login || request.id == (int)Codes::Signup;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request) 
{
    if (!isRequestRelevant(request)) {
        RequestResult errorResult;
        errorResult.newHandler = nullptr; //error
        ErrorResponse err;
        err.message = "request is not relevant";
        errorResult.response = JsonResponsePacketSerializer::serializeResponse(err);
        return errorResult;
    }
    
    if (request.id == (int)Codes::Login) {
        return login(request);
    }
    
    //if request is relevant and not login it must be signup
    return signup(request);
    
}

