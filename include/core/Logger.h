#pragma once
/**
 * Thread‑safe Singleton Logger.
 */
#include <mutex>
#include <string>

class Logger
{
private:
    Logger() = default;
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

public:
    static Logger &instance();
    void log(const std::string &message);
};
