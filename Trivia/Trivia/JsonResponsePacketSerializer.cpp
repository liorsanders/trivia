#include "JsonResponsePacketSerializer.h"
#include <bitset>


std::vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(ErrorResponse& response)
{
	return buildMessage(
		dataToJson<string>(response.message, "message"), response.code);
}

std::vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(LoginResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"), response.code);
}

std::vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(SignupResponse& response)
{
	return buildMessage( 
		dataToJson<unsigned int>(response.status, "status"), response.code);
}

string JsonResponsePacketSerializer::stringToBinary(const string& data)
{
	int length = data.length();
	string binaryData = "";

	for (int i = 0; i < data.length(); i++)
	{
		binaryData += std::bitset<8>(data[i]).to_string();
	}

	return binaryData;
}


std::vector<unsigned char> JsonResponsePacketSerializer::buildMessage
(const std::string& data, const int& messageCode)
{
	string binaryLength = 
		std::bitset<32>(data.length()).to_string(); 

	string binaryCode = 
		std::bitset<8>(messageCode).to_string(); 
	
	string binaryData =
		stringToBinary(data);

	string fullMessage = binaryCode + binaryLength + binaryData;

	return std::vector<unsigned char>(fullMessage.begin(), fullMessage.end());
}
