#include "Room.h"

#include <algorithm>
#include <iterator>
#include <mutex>

std::mutex usersLock;

Room::Room(RoomData metadata) :
	m_metadata(metadata)
{
}

void Room::addUser(LoggedUser user)
{
	std::lock_guard<std::mutex> lock(usersLock);
	
	m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	std::lock_guard<std::mutex> lock(usersLock);

	auto userIt = std::remove(m_users.begin(), m_users.end(), user);

	m_users.erase(userIt, m_users.end());
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> allUsers;

	auto getUsername = [](const LoggedUser& user) 
							{ return user.getUsername(); };

	std::unique_lock<std::mutex> lock(usersLock);

	std::transform(
		m_users.begin(),
		m_users.end(),
		std::back_inserter(allUsers),
		getUsername);

	lock.unlock();

	return allUsers;
}

const RoomData& Room::getRoomData() const
{
	return m_metadata;
}
