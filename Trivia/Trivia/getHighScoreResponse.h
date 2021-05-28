#pragma once

#include <vector>
#include <string>

struct getHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};