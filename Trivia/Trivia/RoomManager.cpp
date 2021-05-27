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
	m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	return m_rooms[id].getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> allRooms;

	auto getRoomData = [](const Room& room)
	{ return room.getRoomData(); };

	std::transform(
		m_rooms.begin(),
		m_rooms.end(),
		allRooms.begin(),
		getRoomData);


	return allRooms;
}
