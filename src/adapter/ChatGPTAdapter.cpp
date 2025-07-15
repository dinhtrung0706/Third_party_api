#include "adapter/ChatGPTAdapter.h"

ChatGPTAdapter::ChatGPTAdapter(ChatGPT_API *api) : api_(api) {}

void ChatGPTAdapter::sendRequest(const std::string &payload)
{
    if (api_)
        api_->callGPT(payload);
}
