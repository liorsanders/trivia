#pragma once

#include <vector>
#include <map>
#include <stdexcept>
#include <string>

#include "Room.h"
#include "RoomData.h"
#include "LoggedUser.h"

class RoomManager
{
public: 
	void createRoom(LoggedUser user, RoomData room);
	void deleteRoom(int id);

	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms() const;

private: 
	std::map<int, Room> m_rooms;
};

class invalidId : public std::logic_error
{
public:
	invalidId();
};