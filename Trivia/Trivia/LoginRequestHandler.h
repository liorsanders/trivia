#pragma once

#include "LoginResponse.h"
#include "SignupResponse.h"
#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestResult.h"
#include "Codes.h"

class LoginRequestHandler : public IRequestHandler 
{

public:
	bool isRequestRelevant(const RequestInfo& request) override;

	RequestResult handleRequest(const RequestInfo& request) override;

private:
	RequestResult HandleLoginRequest(const RequestInfo& request);
	
	RequestResult HandleSignupRequest(const RequestInfo& request);

	RequestResult HandleErrorRequest(const RequestInfo& request);

};