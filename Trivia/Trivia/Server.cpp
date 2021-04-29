#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <fstream>


Server::Server()
{
	m_communicator = Communicator();
}

Server::~Server()
{
}

void Server::run()
{
	m_communicator.startHandleRequests();
}
