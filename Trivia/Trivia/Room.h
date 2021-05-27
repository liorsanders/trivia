#pragma once

#include "RoomData.h"
#include "LoggedUser.h"

#include <string>
#include <vector>

class Room
{
public:
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};
