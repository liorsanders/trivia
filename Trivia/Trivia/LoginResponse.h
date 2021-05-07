#pragma once

#define LOGIN_CODE 21

struct LoginResponse
{
	int code = LOGIN_CODE;

	unsigned int status;
};