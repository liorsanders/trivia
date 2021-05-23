#pragma once

#include "LoginResponse.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestResult.h"
#include "Codes.h"

class LoginRequestHandler : public IRequestHandler {
public:
	bool isRequestRelevant(const RequestInfo& request);
	RequestResult handleRequest(const RequestInfo& request);
};