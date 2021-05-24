#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* res = new LoginRequestHandler;
    return res;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}
