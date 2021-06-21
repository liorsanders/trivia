#pragma once

#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <WinSock2.h>

#include "Room.h"
#include "RoomData.h"
#include "LoggedUser.h"

class RoomManager
{
public: 
	void createRoom(const LoggedUser user, const RoomData roomData);
	void deleteRoom(const int id);

	unsigned int getRoomState(const int id);
	std::vector<RoomData> getRooms() const;

private: 
	std::map<int, Room> m_rooms;
};

class invalidId : public std::logic_error
{
public:
	invalidId();
};