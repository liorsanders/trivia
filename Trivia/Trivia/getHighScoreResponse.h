#pragma once

#include <vector>
#include <string>

struct getHighScoreResponse
{
	std::vector<std::string> usernames;
	std::vector<float> scores;
};