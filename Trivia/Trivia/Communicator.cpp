#include "Communicator.h"
#include <vector>
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "LoginRequestHandler.h"

#define MAX_BYTES 1024

void Communicator::startHandleRequests()
{
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET) 
	{
		throw std::exception(__FUNCTION__ " - socket");
	}

	bindAndListen();

	acceptClients();

	closesocket(m_serverSocket);
}

void Communicator::acceptClients()
{
	while (true) {

		std::cout << "is someone coming? I will wait here...\n" << std::endl;

		SOCKET clientSocket = accept(m_serverSocket, NULL, NULL);

		if (clientSocket == INVALID_SOCKET) 
		{
			throw std::exception(__FUNCTION__);
		}

		std::cout << "someone has arrived:)\n" << std::endl;

		// create handler to the incoming request default is login
		std::shared_ptr<IRequestHandler> requestManager =
			std::make_shared<LoginRequestHandler>();

		m_clients.emplace(socket, requestManager);

		std::thread therad(&Communicator::handleNewClient, this, clientSocket);
		therad.detach();
	}
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	auto serverDetails = Helper::importDetailsFromConfig("config.txt");

	sa.sin_port = htons(serverDetails.second);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	// again stepping out to the global namespace


	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}
	std::cout << "binded successfully!" << std::endl;

	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "I'm really good at listening, so let's do it:)\n" << std::endl;
}

void Communicator::handleNewClient(SOCKET socket)
{

	try
	{
		closesocket(socket);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (...) 
	{
		std::cerr << "Unknown Error!!!" << std::endl;
	}
}

RequestResult Communicator::receiveMessage(const SOCKET& socket)
{
	std::cout << "We should wait for the client :(" << std::endl;

	std::vector<unsigned char> message(MAX_BYTES);
	int result = recv(socket, (char*)message.data(), MAX_BYTES, 0);

	if (result == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";

		s += std::to_string(socket);

		throw std::exception(s.c_str());
	}
	
	auto info = JsonRequestPacketDeserializer::createRequestInfo(message);

	return m_clients[socket]->handleRequest(info);
}

void Communicator::sendMessage(const SOCKET& socket,
	const std::vector<unsigned char>& message)
{
	std::cout << "sending Hello to client...\n" << std::endl;

	if (send(socket, (char*)&message[0], message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}
