#include "adapter/DeepSeekAdapter.h"

DeepSeekAdapter::DeepSeekAdapter(DeepSeek_API *api, const std::string &model) : api_(api), model_(model) {}

void DeepSeekAdapter::setModel(const std::string &model)
{
    model_ = model;
}

void DeepSeekAdapter::sendRequest(const std::string &payload)
{
    if (api_)
        api_->askDeepSeek(payload, model_);
}
