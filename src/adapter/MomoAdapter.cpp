#include "adapter/MomoAdapter.h"
#include <stdexcept>

MomoAdapter::MomoAdapter(Momo_API *api, const std::string &orderInfo) : api_(api), m_orderInfo(orderInfo) {}

void MomoAdapter::sendRequest(const std::string &payload)
{
    if (!api_) {
        throw std::runtime_error("Momo API is not initialized.");
    }

    try {
        double amount = std::stod(payload); // Assuming payload is a string representation of the amount
        api_->createPayment(amount, m_orderInfo);
    } catch (const std::invalid_argument &e) {
        throw std::runtime_error("Invalid payload format: " + std::string(e.what()));
    } catch (const std::exception &e) {
        throw std::runtime_error("Error creating payment: " + std::string(e.what()));
    }

}