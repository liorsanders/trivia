#pragma once

#include "Helper.h"
#include "IRequestHandler.h"
#include <map>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <Windows.h>
#include "RequestResult.h"

class Communicator {
public:
	void startHandleRequests();

	void acceptClients();

private:
	void bindAndListen();
	void handleNewClient(SOCKET);

	RequestResult receiveMessage(const SOCKET& socket);

	void sendMessage(const SOCKET& sc, const std::vector<unsigned char>& message);

	SOCKET m_serverSocket;
	std::map<SOCKET, std::shared_ptr<IRequestHandler>> m_clients;
};