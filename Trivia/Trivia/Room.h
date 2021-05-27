#pragma once

#include "RoomData.h"
#include "LoggedUser.h"

#include <string>
#include <vector>

class Room
{
public:
	Room() = default;
	Room(RoomData metadata);

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);

	std::vector<std::string> getAllUsers();
	RoomData getRoomData();
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

