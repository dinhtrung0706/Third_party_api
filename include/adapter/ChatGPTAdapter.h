#pragma once
/**
 * Adapter: wraps ChatGPT_API to the ThirdPartyAPI interface.
 */
#include "adapter/ThirdPartyAPI.h"
#include "api/ChatGPT_API.h"

class ChatGPTAdapter : public ThirdPartyAPI
{
private:
    ChatGPT_API *api_;

public:
    explicit ChatGPTAdapter(ChatGPT_API *api);
    void sendRequest(const std::string &payload) override;
};
