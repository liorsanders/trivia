#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (int)Codes::CloseRoom == info.id ||
		(int)Codes::Start == info.id ||
		(int)Codes::GetRoomState == info.id;
}



