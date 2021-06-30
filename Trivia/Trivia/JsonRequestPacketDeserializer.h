#pragma once

#include <vector>
#include <array>
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "RequestInfo.h"
#include "GetPlayersInRoomRequest.h"
#include "JoinRoomRequest.h"
#include "CreateRoomRequest.h"
#include "GetPersonalStatsRequest.h"

class JsonRequestPacketDeserializer 
{
public:
	static GetPersonalStatsRequest deserializePersonalStatsRequest
	(const std::vector<unsigned char>& buffer);
	static LoginRequest deserializeLoginRequest
		(const std::vector<unsigned char>& buffer);

	static SignupRequest deserializeSignupRequest
		(const std::vector<unsigned char>& message);	
	
	static RequestInfo createRequestInfo(const std::vector<unsigned char>& message);

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const std::vector<unsigned char>& message);
	static JoinRoomRequest deserializeJoinRoomRequest(const std::vector<unsigned char>& message);
	static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<unsigned char>& message);


private:
	static int extractMessageLength(const std::vector<unsigned char>& message);

	static int fourBytesToInt(const std::array<unsigned char, sizeof(int)>& bytes);
};
