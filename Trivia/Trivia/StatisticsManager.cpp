#include "StatisticsManager.h"
#include <array>
#include <algorithm>

std::vector<std::string> StatisticsManager::getHighScore() const
{
	std::vector<std::string> res;
	auto scores = m_database->getUsersScores();
	std::vector<std::pair<std::string, float>> scoresVector = { scores.begin(), scores.end() };
	std::partial_sort(scoresVector.begin(), scoresVector.end(), scoresVector.begin() + 5,
		[](const auto& lhs, const auto& rhs) {
			return lhs.second > rhs.second;
		});
	for (auto& element : scoresVector)
	{
		res.push_back(element.first);
	}
	std::reverse(res.begin(), res.end());
	return res;
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username) const
{
	std::string numOfGames = std::to_string(m_database->getNumOfPlayerGames(username));
	std::string averageAnswerTime = std::to_string(m_database->getPlayersAverageAnswerTime(username));
	std::string numOfCorrect = std::to_string(m_database->getNumOfCorrectAnswers(username));
	std::string totalNumOfAnswers = std::to_string(m_database->getNumOfTotalAnswers(username));
	return { numOfCorrect, numOfGames, numOfCorrect, totalNumOfAnswers };
}
