#pragma once

#include "IRequestHandler.h"


struct RequestResult
{
	std::vector<unsigned char> response; 
		
	IRequestHandler* newHandler;
};