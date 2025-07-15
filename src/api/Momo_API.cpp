#include "api/Momo_API.h"
#include <iostream>

bool Momo_API::connect(const std::string &api)
{
    // Simulate connecting to the Momo API
    std::cout << "[Momo API] Connecting to " << api << std::endl;
    // Store the API endpoint or perform any necessary setup
    // For this simulation, we assume the connection is always successful
    std::cout << "[Momo API] Connected successfully." << std::endl;
    return true; // Assume connection is always successful for this simulation
}

std::string Momo_API::createPayment(double amount, const std::string &orderInfo)
{
    // Simulate creating a payment
    std::cout << "[Momo API] Creating payment of " << amount << " for order: " << orderInfo << std::endl;
    return "payment_id_12345"; // Return a dummy payment ID
}