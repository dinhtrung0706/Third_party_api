#pragma once
/**
 * Simulated API class for Momo
 */
#include <string>

class Momo_API  // Simulated API class for Momo
{
public:
    // Connect to Momo API
    bool connect(const std::string &api);
    // Create a payment and return the payment ID
    std::string createPayment(double amount, const std::string &orderInfo);
};
