#pragma once

#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(const RequestInfo& request) const override { return false; }
	RequestResult handleRequest(const RequestInfo& request) override {
		return RequestResult();
	}
};	

