#pragma once
#include <vector>
#include "ErrorResponse.h"
#include "SignupResponse.h"
#include "LoginResponse.h"
#include "json.hpp"

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse response)
	{

	}

	static std::vector<unsigned char> serializeResponse(LoginResponse response)
	{

	}

	static std::vector<unsigned char> serializeResponse(SignupResponse response)
	{

	}

private:
	template <typename Response>
	static std::vector<unsigned char> serializeResponse(SignupResponse response)
	{
	}
};

