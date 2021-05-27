#pragma once

#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(const RequestInfo& request) const override;
	RequestResult handleRequest(const RequestInfo& request) override;
};	

