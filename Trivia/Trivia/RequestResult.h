#pragma once

#include "IRequestHandler.h"

class IRequestHandler;

class RequestResult {
public:
	std::vector<unsigned char> response; //buffer
	

	IRequestHandler* newHandler;

};