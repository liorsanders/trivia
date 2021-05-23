#pragma once

#include <string>

class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool doesUserExist(const std::string& username) const = 0;

	virtual bool doesPasswordMatch(const std::string& username,
		const std::string& password) const = 0;

	virtual void addNewUser(const std::string& username,
		const std::string& password, const std::string& mail) = 0;
};