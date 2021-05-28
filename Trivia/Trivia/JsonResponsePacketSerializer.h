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

using std::string; 
using std::vector;

class JsonResponsePacketSerializer
{
public:
	static vector<unsigned char> serializeResponse(ErrorResponse& response);

	static vector<unsigned char> serializeResponse(LoginResponse& response);

	static vector<unsigned char> serializeResponse(SignupResponse& response);

	static vector<unsigned char> serializeResponse(LogoutResponse& response);

	static vector<unsigned char> serializeResponse(GetRoomsResponse& response);

	static vector<unsigned char> serializeResponse(JoinRoomResponse& response);

	static vector<unsigned char> serializerResponse(GetPlayersInRoomResponse& response);


	static vector<unsigned char> serializeResponse(CreateRoomResponse& response);

	static vector<unsigned char> serializeResponse
		(getHighScoreResponse& scoreResponse, getPersonalStatsResponse& statsResponse);

private:
	/*
	* The function receive a template json value to follow the dry convetion.
	*/
	template <typename Value>
	static string dataToJson
		(const vector<Value>& value, const vector <string>& keys)
	{
		nlohmann::json data;
		
		for (size_t i = 0; i < keys.size() && i < value.size(); i++)
		{
			data[keys[i]] = value[i];
		}

		return data.dump();
	}

	static vector<unsigned char>
		buildMessage(const std::string& data, const int& messageCode);

	static std::array<unsigned char, sizeof(int)>
		intToBytes(const uint32_t& length);

};

