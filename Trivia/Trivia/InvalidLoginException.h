#pragma once

#include <exception>
#include <string>
#include <stdexcept>

class InvalidLoginException : public std::logic_error
{
public:
	InvalidLoginException(const std::string& err);
};

