#pragma once
/**
 * Observer interface + a simple concrete observer.
 */
#include <string>

class IRequestObserver
{
public:
    virtual void onRequestSent(const std::string &payload) = 0;
    virtual ~IRequestObserver() = default;
};

class ConsoleObserver : public IRequestObserver
{
public:
    void onRequestSent(const std::string &payload) override;
};
