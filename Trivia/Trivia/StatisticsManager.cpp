#include "StatisticsManager.h"
#include <array>
#include <algorithm>

std::vector<std::pair<std::string, float>> StatisticsManager::getHighScore() const
{
	auto scores = m_database->getUsersScores();
	std::vector<std::pair<std::string, float>> scoresVector = { scores.begin(), scores.end() };
	std::partial_sort(scoresVector.begin(), scoresVector.end(), scoresVector.begin() + 5,
		[](const auto& lhs, const auto& rhs) {
			return lhs.second > rhs.second;
		});
	return scoresVector;
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username) const
{
	std::string numOfGames = std::to_string(m_database->getNumOfPlayerGames(username));
	std::string averageAnswerTime = std::to_string(m_database->getPlayersAverageAnswerTime(username));
	std::string numOfCorrect = std::to_string(m_database->getNumOfCorrectAnswers(username));
	std::string totalNumOfAnswers = std::to_string(m_database->getNumOfTotalAnswers(username));
	return { averageAnswerTime, numOfGames, numOfCorrect, totalNumOfAnswers };
}
