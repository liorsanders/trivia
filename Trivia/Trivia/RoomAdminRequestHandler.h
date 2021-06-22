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
	RoomAdminRequestHandler(Room room, LoggedUser user,
		RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	~RoomAdminRequestHandler() = default;
	bool isRequestRelevant(const RequestInfo& request) const override;
	RequestResult handleRequest(const RequestInfo& request) override;

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

