#pragma once

#include "Codes.h"

struct LoginResponse
{
	unsigned int status;
	const int code = (int)Codes::Login;
};