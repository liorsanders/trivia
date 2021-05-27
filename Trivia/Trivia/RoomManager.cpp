#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData roomData)
{
	Room room = Room(roomData);

	room.addUser(user);
	m_rooms.emplace(roomData.id, room);
}
