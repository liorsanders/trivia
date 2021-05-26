#pragma once

#include "RequestInfo.h"
#include "RequestResult.h"

struct RequestResult;

class IRequestHandler 
{
public:
	virtual ~IRequestHandler() = default;
	virtual bool isRequestRelevant(const RequestInfo& request)const = 0;
	virtual RequestResult handleRequest(const RequestInfo& request) = 0;
};
