#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "Codes.h"

class RoomMemberRequestHandler : public IRequestHandler
{
	RoomMemberRequestHandler(Room, LoggedUser, RoomManager, RequestHandlerFactory);
	~RoomMemberRequestHandler();
	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);

private:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	const RequestResult& createErrorResponse
		(const std::string& error, RequestResult& result);
	RequestResult leaveRoom(RequestInfo);
	RequestResult getRoomState(RequestInfo);
};

