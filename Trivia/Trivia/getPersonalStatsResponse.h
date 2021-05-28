#pragma once

#include <vector>
#include <string>

struct getPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};