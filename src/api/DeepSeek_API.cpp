#include "api/DeepSeek_API.h"
#include <iostream>

void DeepSeek_API::askDeepSeek(const std::string &message, const std::string &model)
{
    std::cout << "[DeepSeek] Query: " << message << " on model: " << model << std::endl;
}
