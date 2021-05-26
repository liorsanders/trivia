#include "InvalidLoginException.h"

InvalidLoginException::InvalidLoginException(const std::string& err) :
	std::logic_error(err.c_str()) {}
