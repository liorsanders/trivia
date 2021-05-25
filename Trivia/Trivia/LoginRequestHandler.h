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
	RequestResult createRequestResult(LoginResponse response);
	
	RequestResult createRequestResult(SignupResponse response);

	RequestResult createRequestResult(ErrorResponse response);

};