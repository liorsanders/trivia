#pragma once
#include <string>

#include "Codes.h"


struct ErrorResponse
{
	int code = (int)Codes::Error;

	std::string message;
};