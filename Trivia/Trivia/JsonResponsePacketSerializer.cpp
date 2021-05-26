#include "JsonResponsePacketSerializer.h"
#include <bitset>

enum class BytesLength {Code = 1, Length = 4};
enum class Bytes { One = 8};

std::vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(ErrorResponse& response)
{
	return buildMessage(
		dataToJson<string>(response.message, "message"), (int)Codes::Error);
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

	// insert length to vector
	std::array<unsigned char, sizeof(int)>bytes = convertUint32ToUint8(length);
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
	JsonResponsePacketSerializer::convertUint32ToUint8
	(const uint32_t& length)
{
	int currentByte = 0;
	std::array<unsigned char, sizeof(int)> bytes = { 0 };

	for (int i = 0; i < sizeof(int); i++)
	{
		currentByte = (int)Bytes::One * (sizeof(int) - i); // calc the current byte and how many bits to shift
		bytes[i] = (length >> currentByte) & 0xFF;
	}

	std::reverse(bytes.begin(), bytes.end()); // because the bytes are in the opposite order

	return bytes;
}