#include "JsonResponsePacketSerializer.h"


std::vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(ErrorResponse& response)
{
	return serialize<std::string>(response.message, "message");
}

std::vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(LoginResponse& response)
{
	return serialize<unsigned int>(response.status, "status");
}

std::vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(SignupResponse& response)
{
	return serialize<unsigned int>(response.status, "status");
}

string JsonResponsePacketSerializer::stringToBinary(const string& data)
{
	int length = data.length();
	string binaryData = "", bin = "";

	for (auto& i : data)
	{
		binaryData += asciiToBytes(int(i)) + " ";
	}

	return binaryData;
}

string JsonResponsePacketSerializer::asciiToBytes(int letter)
{
	string binaryString = "";

	while (letter > 0)
	{
		letter % 2 ? binaryString.push_back('1') : binaryString.push_back('0');
		letter /= 2;
	}

	reverse(binaryString.begin(), binaryString.end());

	return binaryString;
}