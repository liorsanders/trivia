#pragma once

#include "Communicator.h"
#include <WinSock2.h>
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

class Server
{
public:
	Server();
	~Server();
	void run();


private:
	Communicator m_communicator;
	std::shared_ptr<IDatabase> m_database;
	RequestHandlerFactory m_handlerFactory;

};

