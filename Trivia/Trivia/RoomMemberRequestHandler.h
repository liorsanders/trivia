#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "Codes.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room room, LoggedUser user,
		RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	~RoomMemberRequestHandler() = default;
	bool isRequestRelevant(const RequestInfo & request) const override;
	RequestResult handleRequest(const RequestInfo & request) override;

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

