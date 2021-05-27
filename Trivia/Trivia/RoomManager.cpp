#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData roomData)
{
	Room room = Room(roomData);

	m_rooms.emplace(user, room);
}
