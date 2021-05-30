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
#include <mutex>

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

	std::mutex m_mapMutex;
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
};
