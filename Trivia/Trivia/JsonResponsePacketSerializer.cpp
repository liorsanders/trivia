#include "JsonResponsePacketSerializer.h"

#include <bitset>
#include "Bytes.h"

vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(ErrorResponse& response)
{
	vector<string> keys { "message" };
	vector<string> values { response.message };

	return buildMessage(
		dataToJson<string>(values, keys),
		(int)Codes::Error);
}

vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(LoginResponse& response)
{
	vector<string> keys{ "status" };
	vector<unsigned int> values{ response.status };

	return buildMessage(
		dataToJson<unsigned int>(values, keys),
		(int)Codes::Login);
}

vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(SignupResponse& response)
{
	vector<string> keys{ "status" };
	vector<unsigned int> values{ response.status };

	return buildMessage( 
		dataToJson<unsigned int>(values, keys),
		(int)Codes::Signup);
}

vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(LogoutResponse& response)
{
	vector<string> keys{ "status" };
	vector<unsigned int> values{ response.status };

	return buildMessage(
		dataToJson<unsigned int>(values, keys),
		(int)Codes::Logout);
}

vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse& response)
{
	vector<string> keys{ "status" };
	vector<unsigned int> values{ response.status };

	return buildMessage(
		dataToJson<unsigned int>(values, keys),
		(int)Codes::CreateRoom);
}

vector<unsigned char> 
	JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse& response)
{
	vector<string> keys{ "status" };
	vector<unsigned int> values{ response.status };

	return buildMessage(
		dataToJson<unsigned int>(values, keys),
		(int)Codes::JoinRoom);
}

vector<unsigned char> 
JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse& response)
{
	vector<string> keys{ "Rooms" };
	vector<string> values{ string(response.rooms.begin(), response.rooms.end()) };

	return buildMessage(
		dataToJson<string>(values, keys),
		(int)Codes::GetRoom);
}

vector<unsigned char> JsonResponsePacketSerializer::buildMessage
	(const std::string& data, const int& messageCode)
{
	uint32_t length = 
		std::bitset<32>(data.length()).to_ulong(); 
	uint8_t binaryCode = (uint8_t)messageCode;


	// create message vector and build the full message
	vector<unsigned char> fullMessage;

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