#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "json.hpp"
#include "ErrorResponse.h"
#include "SignupResponse.h"
#include "LoginResponse.h"
#include "LogoutResponse.h"
#include "GetRoomsResponse.h"
#include "GetPlayersInRoomResponse.h"
#include "JoinRoomResponse.h"
#include "CreateRoomResponse.h"
#include "getHighScoreResponse.h"
#include "getPersonalStatsResponse.h"
#include "CloseRoomResponse.h"
#include "StartGameResponse.h"
#include "GetRoomStateResponse.h"
#include "LeaveRoomResponse.h"

using std::string; 
using std::vector;

class JsonResponsePacketSerializer
{
public:
	static vector<unsigned char> serializeResponse(ErrorResponse& response);

	static vector<unsigned char> serializeResponse(LoginResponse& response);

	static vector<unsigned char> serializeResponse(SignupResponse& response);

	static vector<unsigned char> serializeResponse(LogoutResponse& response);

	static vector<unsigned char> serializeResponse(CreateRoomResponse& response);
	
	static vector<unsigned char> serializeResponse(JoinRoomResponse& response);

	static vector<unsigned char> serializeResponse(GetRoomsResponse& response);

	static vector<unsigned char> serializeResponse(GetPlayersInRoomResponse& response);

	static vector<unsigned char> serializeResponse
		(getHighScoreResponse& scoreResponse, getPersonalStatsResponse& statsResponse);
	static vector<unsigned char> serializeResponse(getPersonalStatsResponse& statsResponse);
	static vector<unsigned char> serializeResponse(CloseRoomResponse& response);

	static vector<unsigned char> serializeResponse(StartGameResponse& response);

	static vector<unsigned char> serializeResponse(LeaveRoomResponse& response);

	static vector<unsigned char> serializeResponse(GetRoomStateResponse& response);

	static vector<unsigned char> serializeLeaveRoomRequest();

	static vector<unsigned char> serializeStartGameRequest();

private:
	/*
	* The function receive a template json value to follow the dry convetion.
	*/
	template <typename Value>
	static string dataToJson
		(const Value& value, const string& key)
	{
		nlohmann::json data;
		
		data[key] = value;

		return data.dump();
	}

	static vector<unsigned char>
		buildMessage(const std::string& data, const int& messageCode);

	static std::array<unsigned char, sizeof(int)>
		intToBytes(const uint32_t& length);

	static string vectorToString(const vector<string>& vec);

};

