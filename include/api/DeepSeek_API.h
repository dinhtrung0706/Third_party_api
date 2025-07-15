#pragma once
/**
 * Simulated raw DeepSeek SDK.
 */
#include <string>

class DeepSeek_API
{
public:
    void askDeepSeek(const std::string &query, const std::string &model = "deepseek-chat");
};
