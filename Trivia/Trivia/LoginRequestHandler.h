#pragma once

#include "LoginResponse.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestResult.h"
#include "Codes.h"

class LoginRequestHandler : public IRequestHandler 
{

public:
	bool isRequestRelevant(const RequestInfo& request) override;

	RequestResult handleRequest(const RequestInfo& request) override;
private:
    template <class Response, class Handler>
    RequestResult handleRequest(Response response, Handler handler) override
    {
        RequestResult result = RequestResult();
        response.status = 1;

        result.response =
            JsonResponsePacketSerializer::serializeResponse(response);

        result.newHandler = handler;

        return result;
    }
    
};