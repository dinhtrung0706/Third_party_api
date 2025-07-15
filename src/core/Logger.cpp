#include "core/Logger.h"
#include <iostream>

Logger &Logger::instance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string &message)
{
    // Simple console log. Can be extended to log to a file.
    std::cout << "[Logger] " << message << std::endl;
}
