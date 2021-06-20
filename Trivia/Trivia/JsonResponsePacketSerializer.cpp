#include "JsonResponsePacketSerializer.h"

#include <bitset>
#include <algorithm>
#include <numeric>
#include "Bytes.h"

vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(ErrorResponse& response)
{
	return buildMessage(
		dataToJson<string>(response.message, "message"),
		(int)Codes::Error);
}

vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(LoginResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"),
		(int)Codes::Login);
}

vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(SignupResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"),
		(int)Codes::Signup);
}

vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(LogoutResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"),
		(int)Codes::Logout);
}

vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"),
		(int)Codes::CreateRoom);
}

vector<unsigned char>
JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"),
		(int)Codes::JoinRoom);
}

void to_json(nlohmann::json& j, const RoomData& room)
{
	j = {
		{"id", room.id},
		{"name", room.name},
		{"maxPlayers", room.maxPlayers},
		{"timePerQuestion", room.timePerQuestion},
		{"isActive", room.isActive}
	};
}

vector<unsigned char>
	JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse& response)
{
	return buildMessage(
		dataToJson<std::vector<RoomData>>(response.rooms, "Rooms"),
		(int)Codes::GetRoom);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse
(GetPlayersInRoomResponse& response)
{
	return buildMessage(
		dataToJson<string>(vectorToString(response.players), "Players"),
		(int)Codes::GetPlayers);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse
	(getHighScoreResponse& scoreResponse, getPersonalStatsResponse& statsResponse)
{
	string highScores = dataToJson<string>(
		vectorToString(scoreResponse.statistics),
		"HighScores");

	string statistics = dataToJson<string>(
		vectorToString(statsResponse.statistics),
		"UserStatistics");

	return buildMessage(
		statistics + highScores,
		(int)Codes::Statistics);
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

string JsonResponsePacketSerializer::vectorToString(const vector<string>& vec)
{
	const string comma = ", ";
	std::string str = "";

	for (auto& value : vec)
	{
		str += value + ", ";
	}

	str.resize(str.length() - comma.length());

	return str;
}

