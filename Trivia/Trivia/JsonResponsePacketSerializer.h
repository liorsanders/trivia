#pragma once
#include <vector>
#include "ErrorResponse.h"
#include "SignupResponse.h"
#include "LoginResponse.h"
#include "json.hpp"
#include <iostream>
#include <string>

using std::string; 
using std::vector;

class JsonResponsePacketSerializer
{
public:
	static vector<unsigned char> serializeResponse(ErrorResponse& response);

	static vector<unsigned char> serializeResponse(LoginResponse& response);

	static vector<unsigned char> serializeResponse(SignupResponse& response);

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

