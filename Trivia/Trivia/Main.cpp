#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>

int main()
{
	try {
		std::cout << "Server is up!\n" << std::endl;

		WSAInitializer wsaInit;
		Server triviaServer;
		triviaServer.run();
	}
	catch (const std::exception& e) {
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown exception in main !" << std::endl;
	}
	return 0;
}