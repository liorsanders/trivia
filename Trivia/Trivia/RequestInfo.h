#pragma once

#include <vector>
#include <ctime>

class RequestInfo {
public:
	int id; //request id
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};