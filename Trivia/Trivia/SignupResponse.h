#pragma once

#include "Codes.h"

struct SignupResponse
{
	unsigned int status;
	const int code = (int)Codes::Signup;
};