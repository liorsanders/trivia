#pragma once

#include "Communicator.h"
#include <WinSock2.h>
#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>

class Server
{
public:
	void run();


private:

	Communicator m_communicator;
};

