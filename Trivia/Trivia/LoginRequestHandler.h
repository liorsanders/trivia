#pragma once


#include "LoginManager.h"
#include "SignupResponse.h"
#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestResult.h"
#include "RequestHandlerFactory.h"
#include "Codes.h"

class LoginManager;
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{

public:
	LoginRequestHandler(LoginManager& loginManager,
		RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(const RequestInfo& request) const override;

	RequestResult handleRequest(const RequestInfo& request)override;

private:
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);

	const RequestResult& createErrorResponse(const std::string& errorMessage, RequestResult& result);

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};
