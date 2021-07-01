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



vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse& statsResponse)
{
	return buildMessage(
		std::string("{'gamesPlayed': ") + statsResponse.statistics[1] + ", 'answeredRight': " + statsResponse.statistics[2] + ", 'answeredWrong': " + std::to_string(std::stoi(statsResponse.statistics[3]) - std::stoi(statsResponse.statistics[2])) + ", 'averageTime': " + statsResponse.statistics[0] + "}",
		(int)Codes::PersonalStats
	);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"),
		(int)Codes::CloseRoom);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse& response)
{
	std::string json;
	std::string usernames = "['";
	std::string scores = "[";
	for (int i = 0; i < response.usernames.size(); i++) {
		usernames = usernames + response.usernames[i] + "','";
		scores = scores + std::to_string(response.scores[i]) + ",";
	}
	usernames[usernames.size() - 2] = ']';
	scores[scores.size() - 1] = ']';
	json = std::string("{'usernames': ") + usernames.substr(0, usernames.size() - 1) + ", 'scores': " + scores + "}";
	return buildMessage(json, (int)Codes::HighScores);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"),
		(int)Codes::Start);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse& response)
{
	return buildMessage(
		dataToJson<unsigned int>(response.status, "status"),
		(int)Codes::LeaveRoom);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse& response)
{
	return buildMessage(
		dataToJson<GetRoomStateResponse>(response, "RoomState"),
		(int)Codes::GetRoom);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeLeaveRoomRequest()
{
	return buildMessage(
		"",
		(int)Codes::LeaveRoom);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeStartGameRequest()
{
	return buildMessage(
		"",
		(int)Codes::Start);
}

void to_json(nlohmann::json& j, const GetRoomStateResponse& room)
{
	j = {
		{"status", room.status},
		{"hasGameBegun", room.hasGameBegun},
		{"players", room.players},
		{"questionCount", room.questionCount},
		{"answerTimeout", room.answerTimeout}
	};
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

