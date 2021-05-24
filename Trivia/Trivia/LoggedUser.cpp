#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string& username) :
    m_username(username)
{
}

std::string LoggedUser::getUsername() const
{
    return m_username;
}

bool LoggedUser::operator==(LoggedUser const& other)
{
    return this->m_username == other.m_username;
}
