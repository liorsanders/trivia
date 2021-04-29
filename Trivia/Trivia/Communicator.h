#pragma once

#include "IRequestHandler.h"
#include <map>
#include <Windows.h>

class Communicator {
public:
	void startHandleRequests();

private:
	void bindAndListen();
	void handleNewClient(SOCKET);

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler> m_clients;
};