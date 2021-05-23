#pragma once

#include "IRequestHandler.h"
#include <memory>

struct RequestResult
{
	std::vector<unsigned char> response; 
		
	std::shared_ptr<IRequestHandler> newHandler;
};