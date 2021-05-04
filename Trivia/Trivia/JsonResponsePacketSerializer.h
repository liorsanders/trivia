#pragma once
#include <vector>
#include "ErrorResponse.h"
#include "SignupResponse.h"
#include "LoginResponse.h"
#include "json.hpp"
#include <iostream>
#include <algorithm>
#include <string>

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse response);

	static std::vector<unsigned char> serializeResponse(LoginResponse response);

	static std::vector<unsigned char> serializeResponse(SignupResponse response);

private:
	template <typename Response>

	static std::vector<unsigned char> serialize(Response response)
	{
		nlohmann::json data;

		data["status"] = response.status;

		std::string jsonString = data.dump();

		std::string binaryString = stringToBinary(jsonString);

		return std::vector<unsigned char>(binaryString.begin(), binaryString.end());
	}

	static std::string stringToBinary(std::string& data);

	static std::string asciiToBytes(int letter);

};

