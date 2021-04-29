#include "Communicator.h"

void Communicator::startHandleRequests()
{
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET) {
		throw std::exception(__FUNCTION__ " - socket");
	}

	bindAndListen();

	acceptClients();

	closesocket(m_serverSocket);
}

void Communicator::acceptClients()
{
	while (true) {

		std::cout << "accepting client..." << std::endl;

		SOCKET clientSocket = accept(m_serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET) {
			throw std::exception(__FUNCTION__);
		}

		std::cout << "client accepted!" << std::endl;

		//will implement IRequestHandler in later versions
		IRequestHandler requestManager;
		m_clients.insert(std::pair<SOCKET,
			IRequestHandler>(clientSocket, requestManager));

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
	std::cout << "binded" << std::endl;

	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "listening..." << std::endl;
}

void Communicator::handleNewClient(SOCKET socket)
{
	std::string msg = "Hello";

	sendMessage(socket, msg);
	
	receiveMessage(msg, socket);

	closesocket(socket);
}

void Communicator::receiveMessage(std::string& msg, const SOCKET& socket)
{
	std::cout << "waiting for hello back from client..." << std::endl;

	char* data = new char[msg.size() + 1];
	int res = recv(socket, data, msg.size(), 0);
	if (res == INVALID_SOCKET) {
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(socket);
		throw std::exception(s.c_str());
	}

	data[msg.size()] = 0;
	std::cout << "msg back from client: " << data << std::endl;

	delete[] data;
}

void Communicator::sendMessage(const SOCKET& socket, std::string& msg)
{
	std::cout << "sending Hello to client..." << std::endl;

	if (send(socket, msg.c_str(), msg.size(), 0) == INVALID_SOCKET) {
		throw std::exception("Error while sending message to client");
	}
}
