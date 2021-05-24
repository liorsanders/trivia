#pragma once

#include "IRequestHandler.h"

class IRequestHandler;

struct RequestResult
{
	std::vector<unsigned char> response; 
	IRequestHandler* newHandler;
};