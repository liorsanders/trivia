#include "JsonResponsePacketSerializer.h"
#include <bitset>

#define START_MESSAGE_BYTES 5 //because start of message is 5 bytes

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

	fullMessage.insert(
		fullMessage.begin() + START_MESSAGE_BYTES, data.begin(), data.end());

	return fullMessage;
}

/*
* The function convert the length (int - 4 bytes) to separted bytes.
* After, the function insert the bytes into the vector.
*/
void JsonResponsePacketSerializer::insertLengthToVector
	(const uint32_t& length, std::vector<unsigned char>& fullMessage)
{
	for (int i = enumToInt(Bytes::Three); i >= 0; i -= enumToInt(Bytes::one))
	{
		fullMessage.push_back((length >> i) & 0xFF);
	}
}

int JsonResponsePacketSerializer::enumToInt(const Bytes& number)
{
	return static_cast<int>(number);
}
