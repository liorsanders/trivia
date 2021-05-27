#pragma once

#include <map>
#include <vector>
#include "Room.h"
#include "RoomData.h"
#include "LoggedUser.h"

class RoomManager
{
public: 
	void createRoom(LoggedUser user, RoomData room);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();

private: 
	std::map<unsigned int, Room> m_rooms;
};

