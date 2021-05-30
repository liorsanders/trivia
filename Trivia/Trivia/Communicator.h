#pragma once

#include "Helper.h"
#include "IRequestHandler.h"
#include <map>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <Windows.h>
#include "RequestResult.h"
#include "RequestHandlerFactory.h"

class Communicator {
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	void startHandleRequests();

	void acceptClients();

private:
	void bindAndListen();
	void handleNewClient(SOCKET);

	RequestResult receiveMessage(const SOCKET& socket);

	void sendMessage(const SOCKET& sc, const std::vector<unsigned char>& message);

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
};
