#pragma once

#include "Codes.h"

struct SignupResponse
{
	int code = (int)Codes::Signup;

	unsigned int status;
};