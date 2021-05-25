#pragma once
#include <string>
#include "Codes.h"

struct ErrorResponse
{
	std::string message;
	const int code = (int)Codes::Error;
};