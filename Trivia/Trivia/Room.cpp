#include "Room.h"

void Room::addUser(LoggedUser user)
{
	m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	auto userIt = std::remove(m_users.begin(), m_users.end(), user);

	m_users.erase(userIt);
}
