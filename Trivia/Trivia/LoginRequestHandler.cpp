#include "LoginRequestHandler.h"
#include "Codes.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request)
{
    return request.id == (int)Codes::Login;
}

