#pragma once
/**
 * Subject class – orchestrates sending requests
 * and notifies all observers after each send.
 */
#include "adapter/ThirdPartyAPI.h"
#include "core/Observer.h"
#include "core/Logger.h"
#include <vector>
#include <algorithm>
#include <string>

class RequestManager
{
private:
    ThirdPartyAPI *api_;
    std::vector<IRequestObserver *> observers_;

public:
    explicit RequestManager(ThirdPartyAPI *api);

    void attach(IRequestObserver *obs);
    void detach(IRequestObserver *obs);
    void send(const std::string &payload);
};
