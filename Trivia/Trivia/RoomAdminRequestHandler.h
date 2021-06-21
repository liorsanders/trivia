#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "Codes.h"

class RoomAdminRequestHandler :
    public IRequestHandler
{
public: 
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo);

private: 
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	const RequestResult& createErrorResponse
		(const std::string& error, RequestResult& result);
	RequestResult closeRoom(RequestInfo);
	RequestResult startGame(RequestInfo);
	RequestResult getRoomState(RequestInfo);
};

