#include "api/ChatGPT_API.h"
#include <iostream>

void ChatGPT_API::callGPT(const std::string &message)
{
    std::cout << "[ChatGPT] Message: " << message << std::endl;
}
