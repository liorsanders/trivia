#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

int main()
{
	try {
		cout << "starting server..." << endl;

		WSAInitializer wsa_init;
		Server triv_server;
		triv_server.serve();
	}
	catch (const std::exception& e) {
		cout << "Exception was thrown in function: " << e.what() << endl;
	}
	catch (...) {
		cout << "Unknown exception in main !" << endl;
	}
	return 0;
}