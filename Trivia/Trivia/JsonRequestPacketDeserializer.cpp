#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <iostream>
#include "Bytes.h"
#include <algorithm>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest
    (const std::vector<unsigned char>& buffer)
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
    (const std::vector<unsigned char>& buffer)
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

RequestInfo JsonRequestPacketDeserializer::
    createRequestInfo(std::vector<unsigned char>& message)
{
    RequestInfo info = RequestInfo();

    info.id = (int)message[0];

    info.receivalTime = time(nullptr);
    
    int length = extractMessageLength(message);
    
    // cant use std::copy because message and info doesnt has the same size
    auto beginIt = message.begin() + (int)BytesLength::Data;
    info.buffer = std::vector<unsigned char>(beginIt, beginIt + length);

    return info;
}

int JsonRequestPacketDeserializer::extractMessageLength
    (const std::vector<unsigned char>& message)
{
    std::array<unsigned char, sizeof(int)> bytesLength = { 0 };

    std::copy_n(message.begin() + (int)BytesLength::Code,
        (int)BytesLength::Length,
        bytesLength.begin());

    return JsonRequestPacketDeserializer::fourBytesToInt(bytesLength);
}

int JsonRequestPacketDeserializer::fourBytesToInt
    (const std::array<unsigned char, sizeof(int)>& bytes)
{
    int length = int((unsigned char)(bytes[0]) << 24 |
        (unsigned char)(bytes[1]) << 16 |
        (unsigned char)(bytes[2]) << 8 |
        (unsigned char)(bytes[3]));
    
    return length;
}



