#include "LoggedUser.h"

LoggedUser::LoggedUser( const std::string& username) :
    m_username(username)
{ 
}

std::string LoggedUser::getUsername()
{
    return m_username;
}
