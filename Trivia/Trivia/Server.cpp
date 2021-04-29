#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <fstream>


Server::Server()
{
	com = new Communicator;
	m_communicator = *com;
}

Server::~Server()
{
	delete com;
}

void Server::run()
{
	m_communicator.startHandleRequests();
}
