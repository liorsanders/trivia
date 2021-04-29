#pragma once

#include <WinSock2.h>
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>

// Q: why do we need this class ?
// A: this is the main class which holds all the resources,
// accept new clients and handle them.
class Server
{
public:
	Server();
	~Server();
	void serve();


private:
	void importDetailsFromConfig();
	const std::string& extractDetailsFromLine(std::string& line);
	void bindAndListen();
	void acceptClient();
	void clientHandler(SOCKET client_socket);

	SOCKET _socket;
	int serverPort;

	std::string serverIp;

	// Queue for all clients. This way we will know who's the current writer.
	std::deque<std::pair<SOCKET, std::string>> _clients;

};

