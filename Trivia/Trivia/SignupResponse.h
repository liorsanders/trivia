#pragma once

#define SIGNUP_CODE 12

struct SignupResponse
{
	int code = SIGNUP_CODE;

	unsigned int status;
};