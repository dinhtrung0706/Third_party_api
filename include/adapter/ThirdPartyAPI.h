#pragma once
/**
 * Target interface for all third‑party APIs.
 */
#include <string>

class ThirdPartyAPI
{
public:
    virtual void sendRequest(const std::string &payload) = 0;
    virtual ~ThirdPartyAPI() = default;
};
