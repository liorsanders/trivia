#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string& username, SOCKET& sock) :
    m_username(username), m_sock(sock)
{ 
}

std::string LoggedUser::getUsername() const
{
    return m_username;
}

SOCKET LoggedUser::getSocket() const
{
    return m_sock;
}

bool LoggedUser::operator==(LoggedUser const& other)
{
    return this->m_username == other.m_username;
}
