#pragma once

#include "IRequestHandler.h"
#include <memory>

class IRequestHandler;

struct RequestResult
{
	std::vector<unsigned char> response; 
	std::shared_ptr<IRequestHandler> newHandler;
};