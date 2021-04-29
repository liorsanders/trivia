#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <fstream>



void Server::run()
{
	Communicator* com = new Communicator;
	m_communicator = *com;

	m_communicator.startHandleRequests();

	delete com;
}
