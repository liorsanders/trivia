#pragma once

#include <string>

class LoggedUser
{
public: 
	// ctors
	LoggedUser(const std::string& username);

	// dtor
	~LoggedUser() = default;

	// getters
	std::string getUsername() const;	
	
	bool operator==(LoggedUser const& other);

private:
	std::string m_username;

};

