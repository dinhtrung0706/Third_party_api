#include "core/Observer.h"
#include <iostream>

void ConsoleObserver::onRequestSent(const std::string &payload)
{
    std::cout << "[Observer] Sent payload: " << payload << std::endl;
}

