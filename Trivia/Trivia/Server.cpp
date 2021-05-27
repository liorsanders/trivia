#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <fstream>


Server::Server() :  
	m_database(std::make_shared<SqliteDatabase>()),
	m_handlerFactory(RequestHandlerFactory(m_database.get())), 
	m_communicator(Communicator(m_handlerFactory))
{
}

Server::~Server()
{
}

void Server::run()
{
	m_communicator.startHandleRequests();
}
