#include "core/RequestManager.h"

RequestManager::RequestManager(ThirdPartyAPI *api) : api_(api) {}

void RequestManager::attach(IRequestObserver *obs)
{
    // Avoid adding duplicates
    if (std::find(observers_.begin(), observers_.end(), obs) == observers_.end())
    {
        observers_.push_back(obs);
    }
}

void RequestManager::detach(IRequestObserver *obs)
{
    observers_.erase(std::remove(observers_.begin(), observers_.end(), obs), observers_.end());
}

void RequestManager::send(const std::string &payload)
{
    // 1. Log the request
    Logger::instance().log("Sending request: " + payload);

    // 2. Send the request via the adapter
    if (api_)
    {
        api_->sendRequest(payload);
    }

    // 3. Notify all observers
    for (IRequestObserver *obs : observers_)
    {
        obs->onRequestSent(payload);
    }
}
