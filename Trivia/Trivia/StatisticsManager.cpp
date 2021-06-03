#include "StatisticsManager.h"
#include <array>
#include <algorithm>

std::string getName(const std::map<std::string, float>& Map,
    float K)
{
    bool a = true;
    for (auto& it : Map) {
        if (it.second == K) {
            return it.first;
        }
    }
    if (a) {
        return "";
    }
}

std::vector<std::string> StatisticsManager::getHighScore() const
{
	std::array<float, 5> topScores = { -999, -999, -999, -999, -999 };
	std::array<std::string, 5> topUsers;
	const auto scores = m_database->getUsersScores();
	for (auto it = scores.begin(); it != scores.end(); ++it) {
		if (topScores[4] < it->second) {
			topScores[4] = it->second;
		}
		std::sort(topScores.begin(), topScores.end(), std::greater<>());
	}
	for (int i = 0; i < 5; i++) {
		topUsers[i] = getName(scores, topScores[i]);
	}
	return std::vector<std::string>(topUsers.begin(), topUsers.end());
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& usernmae) const
{
	return std::vector<std::string>();
}
