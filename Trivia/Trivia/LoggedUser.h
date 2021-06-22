#pragma once

#include <string>
#include <WinSock2.h>

class LoggedUser
{
public: 
	// ctors
	LoggedUser(const std::string& username, SOCKET& sock);

	// dtor
	~LoggedUser() = default;

	// getters
	std::string getUsername() const;	
	
	bool operator==(LoggedUser const& other);

private:
	std::string m_username;
	SOCKET m_sock;

};

