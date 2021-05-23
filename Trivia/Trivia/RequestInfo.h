#pragma once

#include <vector>
#include <ctime>

struct RequestInfo 
{
	int id; 
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};