#include "Room.h"

#include <algorithm>
#include <iterator>

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

	m_users.erase(userIt, m_users.end());
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> allUsers;

	auto getUsername = [](const LoggedUser& user) 
							{ return user.getUsername(); };

	std::transform(
		m_users.begin(),
		m_users.end(),
		std::back_inserter(allUsers),
		getUsername);


	return allUsers;
}

const RoomData Room::getRoomData() const
{
	return m_metadata;
}
