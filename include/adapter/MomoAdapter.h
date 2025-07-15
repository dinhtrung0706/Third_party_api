#pragma once
/**
 * Adapter: wraps Momo_API to fit the ThirdPartyAPI interface.
 */
#include "adapter/ThirdPartyAPI.h"
#include "api/Momo_API.h"

class MomoAdapter : public ThirdPartyAPI
{
private:
    Momo_API *api_;
    std::string m_orderInfo;

public:
    explicit MomoAdapter(Momo_API *api, const std::string &orderInfo);
    void sendRequest(const std::string &payload) override;
};
