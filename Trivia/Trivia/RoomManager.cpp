#include "RoomManager.h"

#include <algorithm>

void RoomManager::createRoom(LoggedUser user, RoomData roomData)
{
	Room room = Room(roomData);

	room.addUser(user);
	m_rooms.emplace(roomData.id, room);
}

void RoomManager::deleteRoom(int id) 
{
	bool isIdInvalid = m_rooms.find(id) == m_rooms.end();

	if (isIdInvalid)
	{
		throw invalidId();
	}
	
	m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	bool isIdInvalid = m_rooms.find(id) == m_rooms.end();

	if (isIdInvalid)
	{
		throw invalidId();
	}

	return m_rooms[id].getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms() const
{
	std::vector<RoomData> allRooms;

	auto getRoomData = [](std::pair<unsigned int, Room> room)
	{ return room.second.getRoomData(); };

	std::transform(
		m_rooms.begin(),
		m_rooms.end(),
		allRooms.begin(),
		getRoomData);


	return allRooms;
}

invalidId::invalidId() : 
	std::logic_error("id wasn't found on the map!")
{
}
