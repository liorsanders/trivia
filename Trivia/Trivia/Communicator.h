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

	void acceptClients();

private:
	void bindAndListen();
	void handleNewClient(SOCKET);

	void receiveMessage(std::string& msg, const SOCKET& socket);

	void sendMessage(const SOCKET& sc, std::string& msg);

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler> m_clients;
};