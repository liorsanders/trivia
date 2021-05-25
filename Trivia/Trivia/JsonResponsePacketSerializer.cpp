#include "JsonResponsePacketSerializer.h"
#include <bitset>
#include "Bytes.h"

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
	uint8_t binaryCode = (uint8_t)messageCode;


	// create message vector and build the full message
	std::vector<unsigned char> fullMessage;

	fullMessage.push_back(binaryCode);

	// insert length to vector
	std::array<unsigned char, sizeof(int)>bytes = intToBytes(length);
	auto start = fullMessage.begin() + (int)BytesLength::Code;
	fullMessage.insert(
		start, bytes.begin(), bytes.end());
	
	// insert data to vector
	start = fullMessage.begin() + (int)BytesLength::Code + (int)BytesLength::Length;
	fullMessage.insert(
		start, data.begin(), data.end());

	return fullMessage;
}

/*
* The function convert the length (int - 4 bytes) to separted bytes.
* After, the function insert the bytes into the vector.
*/
std::array<unsigned char, sizeof(int)>
	JsonResponsePacketSerializer::intToBytes(const uint32_t& length)
{
	std::array<unsigned char, sizeof(int)> bytes = { 0 };

	bytes[0] = length >> 24;
	bytes[1] = length >> 16;
	bytes[2] = length >> 8;
	bytes[3] = length;

	return bytes;
}