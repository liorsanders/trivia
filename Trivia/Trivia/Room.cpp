#include "Room.h"

#include <algorithm>

Room::Room(RoomData metadata) :
	m_metadata(metadata)
{
}

void Room::addUser(LoggedUser user)
{
	m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	auto userIt = std::remove(m_users.begin(), m_users.end(), user);

	m_users.erase(userIt);
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> allUsers;

	auto getUsername = [](const LoggedUser& user) 
							{ return user.getUsername(); };

	std::transform(
		m_users.begin(),
		m_users.end(),
		allUsers.begin(),
		getUsername);


	return allUsers;
}

unsigned int Room::isRoomActive()
{
	return m_metadata.isActive;
}
