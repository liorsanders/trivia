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

	std::vector<std::string> getAllUsers() const;
	std::vector<LoggedUser> getLoggedUsers() const;
	const RoomData& getRoomData() const;

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

