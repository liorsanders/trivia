#pragma once

#include <vector>
#include "LoginRequest.h"
#include "SignupRequest.h"

class JsonRequestPacketDeserializer 
{
public:
	static LoginRequest deserializeLoginRequest
		(std::vector<unsigned char> buffer);

	static SignupRequest deserializeSignupRequest
		(std::vector<unsigned char> buffer);	
};