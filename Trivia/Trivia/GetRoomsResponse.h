#pragma once

#include <vector>

#include "RoomData.h"

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};