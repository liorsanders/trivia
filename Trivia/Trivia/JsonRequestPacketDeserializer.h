#pragma once

#include <vector>
#include <array>
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "RequestInfo.h"

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest
	(const std::vector<unsigned char>& buffer);

	static SignupRequest deserializeSignupRequest
	(const std::vector<unsigned char>& message);

	static RequestInfo createRequestInfo(const std::vector<unsigned char>& message);

private:
	static int extractMessageLength(const std::vector<unsigned char>& message);

	static int fourBytesToInt(const std::array<unsigned char, sizeof(int)>& bytes);
};
