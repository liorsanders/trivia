#pragma once

#include "IRequestHandler.h"
#include <memory>

class IRequestHandler;

struct RequestResult
{
	std::vector<unsigned char> response; 
	IRequestHandler* newHandler;
};