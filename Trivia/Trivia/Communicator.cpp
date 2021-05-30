#include "Communicator.h"
#include <vector>
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "LoginRequestHandler.h"

#define MAX_BYTES 1024

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : 
	m_handlerFactory(handlerFactory), m_serverSocket(0)

{
}
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
		

		auto loginHandler = m_handlerFactory.createLoginRequestHandler();
		//TODO add lock support here
		m_clients.insert({ clientSocket, loginHandler });

		std::thread therad(&Communicator::handleNewClient, this, clientSocket);
		therad.detach();
		//handleNewClient(clientSocket);
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
	LoginManager manager = m_handlerFactory.getLoginManager();

	IRequestHandler* requestManager = 
		new LoginRequestHandler(manager, m_handlerFactory);

	m_clients.emplace(socket, requestManager);

	try
	{
		while (m_clients[socket] != nullptr)
		{
			std::cout << "recieving message" << std::endl;
			RequestResult result = receiveMessage(socket);
			auto signup = JsonRequestPacketDeserializer::deserializeSignupRequest(result.response);
			std::cout << "email: " << signup.email << " username: " << signup.username << " password: " <<
				signup.password << std::endl;

			sendMessage(socket, result.response);

			auto key = m_clients.find(socket);

			if(key != m_clients.end())
				m_clients.erase(key);

			m_clients.emplace(socket, result.newHandler);
		}

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
	std::cout << "sending message to client...\n" << std::endl;

	bool isMessageInvalid = 
		!message.empty() && 
		send(socket, (char*)&message[0], message.size(), 0) ==
		INVALID_SOCKET;

	if (isMessageInvalid)
	{
		throw std::exception("Error while sending message to client");
	}
}
