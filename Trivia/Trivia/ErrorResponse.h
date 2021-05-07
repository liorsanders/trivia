#pragma once
#include <string>

#define ERROR_CODE 3


struct ErrorResponse
{
	int code = ERROR_CODE;

	std::string message;
};