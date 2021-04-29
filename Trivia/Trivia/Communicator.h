#pragma once

#include "Helper.h"
#include "IRequestHandler.h"
#include <map>
#include <iostream>
#include <thread>
#include <WinSock2.h>
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