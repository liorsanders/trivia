#pragma once
#include <vector>
#include "ErrorResponse.h"
#include "SignupResponse.h"
#include "LoginResponse.h"
#include "json.hpp"
#include <iostream>
#include <algorithm>
#include <string>

using std::string;

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse& response);

	static std::vector<unsigned char> serializeResponse(LoginResponse& response);

	static std::vector<unsigned char> serializeResponse(SignupResponse& response);

private:
	template <typename Value>

	static std::vector<unsigned char> serialize(Value& jsonValue, const string& jsonKey) 
	{
		nlohmann::json data;

		data[jsonKey] = jsonValue;

		string jsonString = data.dump();

		string binaryString = stringToBinary(jsonString);

		return std::vector<unsigned char>(binaryString.begin(), binaryString.end());
	}

	static string stringToBinary(const string& data);

	static string asciiToBytes(int letter);

};

