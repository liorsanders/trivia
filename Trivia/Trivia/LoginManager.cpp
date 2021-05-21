#include "LoginManager.h"
#include <algorithm>

LoginManager::LoginManager()
{
	m_database = std::make_shared<SqliteDatabase>();
}

LoginManager::~LoginManager()
{
}

