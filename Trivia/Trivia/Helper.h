#pragma once

#include <tuple>
#include <string>
#include <fstream>
#include "RequestInfo.h"

class Helper 
{
public:
	//return ip, port
	static std::pair<std::string, int> importDetailsFromConfig(std::string configName);
	static const std::string extractDetailsFromLine(std::string& line);
};