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
private:
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory):
	m_loginManager(loginManager), m_handlerFactory(handlerFactory) {}
	bool isRequestRelevant(const RequestInfo& request) const override;

	RequestResult handleRequest(const RequestInfo& request)override;
};
