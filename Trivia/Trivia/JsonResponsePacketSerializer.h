#pragma once
#include <vector>
#include "ErrorResponse.h"
#include "SignupResponse.h"
#include "LoginResponse.h"
#include "json.hpp"
#include <iostream>
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

	/*
	* The function receive a template json value to follow the dry convetion.
	*/
	static string dataToJson(Value& jsonValue, const string& jsonKey) 
	{
		nlohmann::json data;

		data[jsonKey] = jsonValue;

		return data.dump();
	}

	static std::vector<unsigned char>
		buildMessage(const std::string& data, const int& messageCode);

	static void insertLengthToVector
		(const uint32_t& length, std::vector<unsigned char>& fullMessage);

	static void insertDataToVector
		(string data, std::vector<unsigned char>& fullMessage);
};

