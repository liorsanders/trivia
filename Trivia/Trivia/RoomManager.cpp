#include "RoomManager.h"

#include <algorithm>
#include <mutex>

std::mutex roomLock;

void RoomManager::createRoom(const LoggedUser user, const RoomData roomData)
{
	Room room = Room(roomData);

	room.addUser(user);

	std::lock_guard<std::mutex> lock(roomLock);

	m_rooms.emplace(roomData.id, room);
}

void RoomManager::deleteRoom(const int id) 
{
	bool isIdInvalid = m_rooms.find(id) == m_rooms.end();

	if (isIdInvalid)
	{
		throw invalidId();
	}
	
	std::lock_guard<std::mutex> lock(roomLock);

	m_rooms.erase(id);
}

std::vector<LoggedUser> RoomManager::getLoggedUser(const int id)
{
	bool isIdInvalid = m_rooms.find(id) == m_rooms.end();

	if (isIdInvalid)
	{
		throw invalidId();
	}

	std::lock_guard<std::mutex> lock(roomLock);

	return m_rooms[id].getLoggedUsers();
}

unsigned int RoomManager::getRoomState(const int id)
{
	bool isIdInvalid = m_rooms.find(id) == m_rooms.end();

	if (isIdInvalid)
	{
		throw invalidId();
	}

	std::lock_guard<std::mutex> lock(roomLock);

	return m_rooms[id].getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms() const
{
	std::vector<RoomData> allRooms;

	auto getRoomData = [](std::pair<unsigned int, Room> room)
	{ return room.second.getRoomData(); };

	std::unique_lock<std::mutex> lock(roomLock);

	std::transform(
		m_rooms.begin(),
		m_rooms.end(),
		allRooms.begin(),
		getRoomData);
		
	lock.unlock();

	return allRooms;
}

invalidId::invalidId() : 
	std::logic_error("id wasn't found on the map!")
{
}
