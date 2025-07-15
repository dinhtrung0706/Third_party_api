#pragma once
/**
 * Simulated raw ChatGPT SDK.
 */
#include <string>

class ChatGPT_API
{
public:
    void callGPT(const std::string &message);
};
