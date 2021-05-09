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

std::vector<unsigned char> JsonResponsePacketSerializer::buildMessage
	(const std::string& data, const int& messageCode)
{
	uint32_t length = 
		std::bitset<32>(data.length()).to_ulong(); 

	uint8_t binaryCode = 
		std::bitset<8>(messageCode).to_ulong();


	// create message vector and build the full message
	std::vector<unsigned char> fullMessage;

	fullMessage.push_back(binaryCode);
	insertLengthToVector(length, fullMessage);
	insertDataToVector(data, fullMessage);

	return fullMessage;
}

/*
* The function convert the length (int - 4 bytes) to separted bytes.
* After, the function insert the bytes into the vector.
*/
void JsonResponsePacketSerializer::insertLengthToVector
	(const uint32_t& length, std::vector<unsigned char>& fullMessage)
{
	for (int i = 24; i >=0; i -= 8)
	{
		fullMessage.push_back((length >> i) & 0xFF);
	}
}

/*
* The function push the chars from the data to the vector.
*/
void JsonResponsePacketSerializer::
	insertDataToVector(string data, std::vector<unsigned char>& fullMessage)
{
	for (auto& letter : data)
	{
		fullMessage.push_back(letter);
	}
}
