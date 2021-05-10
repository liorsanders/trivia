#pragma once

#include "Codes.h"

struct LoginResponse
{
	int code = (int)Codes::Login;

	unsigned int status;
};