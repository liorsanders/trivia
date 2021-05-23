#pragma once

#include "RequestInfo.h"
#include "RequestResult.h"

class RequestResult; //circular reference

class IRequestHandler {
public:
	virtual bool isRequestRelevant(const RequestInfo& request) = 0;
	virtual RequestResult handleRequest(const RequestInfo& request) = 0;
};