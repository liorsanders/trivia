#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* res = new LoginRequestHandler(this->m_loginManager, this);
    return res;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}
