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
	string binaryData = "", bin = "";

	for (auto& i : data)
	{
		binaryData += asciiToBytes(int(i));
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
