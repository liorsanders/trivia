#pragma once

#include "SqliteDatabase.h"
#include <string>
#include <vector>

class StatisticsManager
{
public:
	std::vector<std::string> getHighScore() const;
	std::vector<std::string> getUserStatistics(const std::string& username) const;
private:
	IDatabase* m_database;
};

