#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <fstream>

//static const unsigned int IFACE = 0;
//
//
//Server::Server()
//{
//	// notice that we step out to the global namespace
//	// for the resolution of the function socket
//	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (_socket == INVALID_SOCKET)
//		throw std::exception(__FUNCTION__ " - socket");
//
//	importDetailsFromConfig();
//}
//
//Server::~Server()
//{
//	std::cout << __FUNCTION__ " closing accepting socket" << std::endl;
//	// why is this try necessarily ?
//	try
//	{
//		// the only use of the destructor should be for freeing 
//		// resources that was allocated in the constructor
//		::closesocket(_socket);
//	}
//	catch (...) {}
//}
//
//void Server::serve()
//{
//	bindAndListen();
//
//
//	while (true)
//	{
//		// the main thread is only accepting clients 
//		// and add then to the list of handlers
//		std::cout << "accepting client..." << std::endl;
//		acceptClient();
//	}
//
//}
//
//
//void Server::importDetailsFromConfig()
//{
//	std::ifstream config("config.txt");
//	std::string line = "";
//
//	// extract server ip
//	std::getline(config, line);
//	serverIp = extractDetailsFromLine(line);
//
//	// extract server port
//	std::getline(config, line);
//	serverPort = stoi(extractDetailsFromLine(line));
//
//}
//
//const std::string& Server::extractDetailsFromLine(std::string& line)
//{
//	return line.substr(line.find_first_of('='), line.length());
//}
//
//// listen to connecting requests from clients
//// accept them, and create thread for each client
//void Server::bindAndListen()
//{
//	struct sockaddr_in sa = { 0 };
//	sa.sin_port = htons(serverPort);
//	sa.sin_family = AF_INET;
//	sa.sin_addr.s_addr = INADDR_ANY;
//
//	// again stepping out to the global namespace
//	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
//	{
//		throw std::exception(__FUNCTION__ " - bind");
//	}
//	std::cout << "binded" << std::endl;
//
//	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
//		throw std::exception(__FUNCTION__ " - listen");
//	std::cout << "listening..." << std::endl;
//}
//
//void Server::acceptClient()
//{
//	SOCKET client_socket = accept(_socket, NULL, NULL);
//	if (client_socket == INVALID_SOCKET)
//		throw std::exception(__FUNCTION__);
//
//	std::cout << "Client accepted !" << std::endl; 
//
//	 create new thread for client	and detach from it
//	std::thread tr(&Server::clientHandler, this, client_socket);
//	tr.detach();
//
//}
//	