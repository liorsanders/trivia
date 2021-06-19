#include "RoomMemberRequestHandler.h"

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    return (int)Codes::Start == info.id ||
        (int)Codes::GetRoomState == info.id ||
        (int)Codes::LeaveRoom == info.id;
}
