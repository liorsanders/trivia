#include "Helper.h"
#include "Bytes.h"

std::pair<std::string, int> Helper::importDetailsFromConfig(std::string configName)
{
	std::ifstream config(configName);

	if (!config.is_open()) 
	{

		std::string error = "Error: failt to open " + configName;
		throw std::exception(error.c_str());
	}

	std::string line = "";

	// extract server ip
	std::getline(config, line);
	std::string serverIp = extractDetailsFromLine(line);

	// extract server port
	std::getline(config, line);
	int serverPort = stoi(extractDetailsFromLine(line));

	return { serverIp, serverPort };
}

const std::string Helper::extractDetailsFromLine(std::string& line)
{
	int pos = line.find('=') + 1;

	return line.substr(pos);
}
