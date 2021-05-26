#pragma once

#include "IRequestHandler.h"
#include <vector>

class IRequestHandler;

struct RequestResult
{
	std::vector<unsigned char> response; 
	IRequestHandler* newHandler;
};
