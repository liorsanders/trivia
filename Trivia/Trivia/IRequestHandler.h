#pragma once

#include "RequestInfo.h"
#include "RequestResult.h"
#include <WinSock2.h>
struct RequestResult;

class IRequestHandler 
{
public:
	virtual ~IRequestHandler() = default;
	virtual bool isRequestRelevant(const RequestInfo& request)const = 0;
	virtual RequestResult handleRequest(const RequestInfo& request) = 0;
	SOCKET m_sock;
};
