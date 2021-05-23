#include "Helper.h"

std::pair<std::string, int> Helper::importDetailsFromConfig(std::string configName)
{
	std::ifstream config(configName);
	if (!config.is_open()) {
		throw std::exception((std::string("failed to open: ") + configName).c_str());
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
	int found_at = line.find('=');
	return line.substr(line.find('=')+1, line.length()-found_at);
}

RequestInfo Helper::createRequestInfo(std::vector<unsigned char> buffer)
{
	RequestInfo info = RequestInfo();

	info.id = (int)buffer[0];

	info.receivalTime = time(nullptr);

	return RequestInfo();
}
