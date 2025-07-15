#pragma once
/**
 * Adapter: wraps DeepSeek_API to the ThirdPartyAPI interface.
 */
#include "adapter/ThirdPartyAPI.h"
#include "api/DeepSeek_API.h"
#include <string>

class DeepSeekAdapter : public ThirdPartyAPI
{
private:
    DeepSeek_API *api_;
    std::string model_;

public:
    explicit DeepSeekAdapter(DeepSeek_API *api, const std::string &model = "deepseek-chat");
    void setModel(const std::string &model);
    void sendRequest(const std::string &payload) override;
};
