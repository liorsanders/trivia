#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <fstream>


Server::Server() : 
	m_database(new SqliteDatabase), 
	m_handlerFactory(RequestHandlerFactory(m_database)), 
	m_communicator(Communicator(m_handlerFactory))
{

}

Server::~Server()
{
	delete m_database;
}

void Server::run()
{
	m_communicator.startHandleRequests();
}
