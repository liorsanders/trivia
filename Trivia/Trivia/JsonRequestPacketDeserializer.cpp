#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <iostream>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest
    (std::vector<unsigned char> buffer)
{
    LoginRequest request = LoginRequest();

    // json can accept string as a paramter so we convert the vector to string
    nlohmann::json data = nlohmann::json::parse(
        std::string(buffer.begin(), buffer.end()));

    // in case some one try to trick us and there is no user name
    try
    {
        request.username = data["username"];
        request.password = data["password"];
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }
 
    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest
    (std::vector<unsigned char> buffer)
{
    SignupRequest request = SignupRequest();

    // json can accept string as a paramter so we convert the vector to string
    nlohmann::json data = nlohmann::json::parse(
        std::string(buffer.begin(), buffer.end()));

    // in case some one try to trick us and there is no user name
    try
    {
        request.username = data["username"];
        request.password = data["password"];
        request.email = data["email"];
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }

    return request;
}
