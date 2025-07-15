# Walkthrough: Third-Party API Integration

This document provides a step-by-step walkthrough of the project, explaining the existing code structure and guiding you through the implementation of the missing parts, based on the `docs/BT2 Third-party API.pdf`.

## 1. Understanding the Problem

As outlined in the PDF, the main goal is to create a system that can interact with multiple third-party APIs (like ChatGPT and DeepSeek) in a unified, maintainable, and observable way. Each API has a different interface, which we need to standardize.

- **ChatGPT API**: `void callGPT(const std::string &message);`
- **DeepSeek API**: `void askDeepSeek(const std::string &query, const std::string &model = "deepseek-chat");`

## 2. Step 1: Standardizing APIs with the Adapter Pattern

The **Adapter Pattern** is used to provide a consistent interface for different APIs.

### The Target Interface (`ThirdPartyAPI.h`)

The `include/adapter/ThirdPartyAPI.h` file defines the standard interface that all our API adapters will conform to:

```cpp
class ThirdPartyAPI
{
public:
    virtual void sendRequest(const std::string &payload) = 0;
    virtual ~ThirdPartyAPI() = default;
};
```

Any part of our system that needs to send a request will do so by calling the `sendRequest` method.

### The `ChatGPTAdapter`

The `ChatGPTAdapter` (`include/adapter/ChatGPTAdapter.h` and `src/adapter/ChatGPTAdapter.cpp`) wraps the `ChatGPT_API` and implements the `ThirdPartyAPI` interface.

**Implementation (`src/adapter/ChatGPTAdapter.cpp`):**
```cpp
#include "adapter/ChatGPTAdapter.h"

ChatGPTAdapter::ChatGPTAdapter(ChatGPT_API *api) : api_(api) {}

void ChatGPTAdapter::sendRequest(const std::string &payload)
{
    if (api_)
        api_->callGPT(payload);
}
```
This is a complete and straightforward implementation. It takes a `ChatGPT_API` object and translates the `sendRequest` call into a `callGPT` call.

### **Action Required**: Implement `DeepSeekAdapter`

The implementation for `DeepSeekAdapter` is missing in `src/adapter/DeepSeekAdapter.cpp`. You need to implement the `sendRequest` method to call the `askDeepSeek` method of the `DeepSeek_API`.

**File to edit: `src/adapter/DeepSeekAdapter.cpp`**

```cpp
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
```

## 3. Step 2: Centralizing Requests with `RequestManager`

The `RequestManager` (`include/core/RequestManager.h`) is the central class responsible for sending requests through the adapters. It also acts as the **Subject** in the Observer pattern.

### **Action Required**: Implement `RequestManager`

The implementation in `src/core/RequestManager.cpp` is missing. You need to implement the `attach`, `detach`, and `send` methods.

**File to edit: `src/core/RequestManager.cpp`**

```cpp
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
```

## 4. Step 3: System-Wide Logging with Singleton `Logger`

The `Logger` (`include/core/Logger.h`) is a **Singleton** that ensures only one logging instance exists throughout the application.

### **Action Required**: Implement `Logger`

The implementation in `src/core/Logger.cpp` is missing. You need to implement the `instance()` and `log()` methods.

**File to edit: `src/core/Logger.cpp`**

```cpp
#include "core/Logger.h"
#include <iostream>

Logger &Logger::instance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string &message)
{
    // Simple console log. Can be extended to log to a file.
    std::cout << "[LOG]: " << message << std::endl;
}
```

## 5. Step 4: Monitoring Requests with the Observer Pattern

The **Observer Pattern** allows multiple objects to be notified when a request is sent. The interface is defined in `include/core/Observer.h`.

### The Observer Interface (`IRequestObserver`)

```cpp
class IRequestObserver
{
public:
    virtual void onRequestSent(const std::string &payload) = 0;
    virtual ~IRequestObserver() = default;
};
```

### **Action Required**: Implement `ConsoleObserver`

A simple concrete observer, `ConsoleObserver`, is declared in `Observer.h`, but its implementation is missing in `src/core/Observer.cpp`.

**File to edit: `src/core/Observer.cpp`**

```cpp
#include "core/Observer.h"
#include <iostream>

void ConsoleObserver::onRequestSent(const std::string &payload)
{
    std::cout << "[ConsoleObserver]: Request sent with payload - " << payload << std::endl;
}
```

## 6. Step 5: Testing the System

The `unit_test/` directory contains the testing framework. After implementing the missing parts, you can compile and run the tests to verify the functionality. The tests will likely cover:
- Sending requests to both ChatGPT and DeepSeek.
- Attaching and detaching observers.
- Verifying that the logger is called.

## Summary of Actions

1.  **Implement `DeepSeekAdapter`**: In `src/adapter/DeepSeekAdapter.cpp`.
2.  **Implement `RequestManager`**: In `src/core/RequestManager.cpp`.
3.  **Implement `Logger`**: In `src/core/Logger.cpp`.
4.  **Implement `ConsoleObserver`**: In `src/core/Observer.cpp`.

Once these steps are completed, the system will be fully functional as described in the PDF.

---

## 7. Extension Walkthrough (Question 2)

This section covers the extension questions from the PDF, focusing on enhancing the system with more advanced features.

### 7.1. (a) Integrating a New Payment API (e.g., Momo)

The Adapter pattern makes it easy to integrate new APIs without changing the core logic. Let's assume we have a `Momo_API` with the following interface:

```cpp
// Hypothetical Momo API
class Momo_API {
public:
    // Connects to the Momo service
    bool connect(const std::string& apiKey);
    // Creates a payment and returns a transaction ID
    std::string createPayment(double amount, const std::string& orderInfo);
};
```

**Step 1: Create the `MomoAdapter`**

First, create the header file `include/adapter/MomoAdapter.h`:

```cpp
#ifndef MOMO_ADAPTER_H
#define MOMO_ADAPTER_H

#include "adapter/ThirdPartyAPI.h"
#include "api/Momo_API.h" // Assuming this file exists

class MomoAdapter : public ThirdPartyAPI {
private:
    Momo_API* m_api;
    std::string m_orderInfo;

public:
    MomoAdapter(Momo_API* api, const std::string& orderInfo);
    void sendRequest(const std::string& payload) override;
};

#endif // MOMO_ADAPTER_H
```

Next, create the implementation file `src/adapter/MomoAdapter.cpp`:

```cpp
#include "adapter/MomoAdapter.h"
#include <stdexcept> // For std::stod

MomoAdapter::MomoAdapter(Momo_API* api, const std::string& orderInfo)
    : m_api(api), m_orderInfo(orderInfo) {}

void MomoAdapter::sendRequest(const std::string& payload) {
    if (m_api) {
        try {
            // The payload for a payment request is expected to be the amount
            double amount = std::stod(payload);
            m_api->createPayment(amount, m_orderInfo);
        } catch (const std::invalid_argument& e) {
            // Handle cases where payload is not a valid number
            Logger::instance().log("Error: Invalid payload for Momo payment. Expected a number.");
        }
    }
}
```

**Step 2: Use the `MomoAdapter` in `main`**

You can now use this new adapter just like the others.

```cpp
#include "adapter/MomoAdapter.h"
#include "api/Momo_API.h"

int main() {
    // ... existing setup ...

    // Using the Momo API
    Momo_API momoApi;
    momoApi.connect("YOUR_MOMO_API_KEY");

    MomoAdapter momoAdapter(&momoApi, "Payment for services");
    RequestManager momoRequestManager(&momoAdapter);

    momoRequestManager.send("50000"); // Send a request to create a 50,000 VND payment

    return 0;
}
```

### 7.2. (b) Tracking Costs with a `CostObserver`

We can create a new observer to monitor the "cost" of each request. For AI APIs, this could be based on token count; for payment APIs, it's the transaction amount.

**Step 1: Create the `CostObserver`**

Create the header `include/core/CostObserver.h`:

```cpp
#ifndef COST_OBSERVER_H
#define COST_OBSERVER_H

#include "core/Observer.h"

class CostObserver : public IRequestObserver {
private:
    double m_totalCost;

public:
    CostObserver();
    void onRequestSent(const std::string& payload) override;
    double getTotalCost() const;
};

#endif // COST_OBSERVER_H
```

And its implementation in `src/core/CostObserver.cpp`:

```cpp
#include "core/CostObserver.h"
#include "core/Logger.h"
#include <string>

CostObserver::CostObserver() : m_totalCost(0.0) {}

void CostObserver::onRequestSent(const std::string& payload) {
    // Simple logic: assume payload is a cost/token count
    try {
        double cost = std::stod(payload);
        m_totalCost += cost;
        Logger::instance().log("CostObserver: Request processed. Cost: " + payload + ". Total cost: " + std::to_string(m_totalCost));
    } catch (const std::invalid_argument&) {
        // For non-numeric payloads (like AI prompts), estimate cost based on length
        double estimatedCost = payload.length() * 0.01; // Example: 0.01 units per character
        m_totalCost += estimatedCost;
        Logger::instance().log("CostObserver: Request processed. Estimated cost: " + std::to_string(estimatedCost) + ". Total cost: " + std::to_string(m_totalCost));
    }
}

double CostObserver::getTotalCost() const {
    return m_totalCost;
}
```

**Step 2: Attach the `CostObserver`**

In your `main` function or test cases, attach this observer to the `RequestManager`.

```cpp
#include "core/CostObserver.h"

int main() {
    // ...
    RequestManager deepSeekRequestManager(&deepSeekAdapter);
    CostObserver costTracker;
    deepSeekRequestManager.attach(&costTracker);

    deepSeekRequestManager.send("Tell me a joke.");
    deepSeekRequestManager.send("Write a short story.");

    // ...
    RequestManager momoRequestManager(&momoAdapter);
    momoRequestManager.attach(&costTracker);
    momoRequestManager.send("50000");

    std::cout << "Final total cost across all services: " << costTracker.getTotalCost() << std::endl;

    return 0;
}
```

### 7.3. (c) Adding Trace IDs and Timestamps

To improve logging and debugging, we can modify the `RequestManager` to generate a unique trace ID and timestamp for each request.

**Step 1: Modify `RequestManager` and `Logger`**

Update `RequestManager::send` to generate this metadata and pass it to the logger and observers.

**File to edit: `include/core/RequestManager.h`**
```cpp
// Add includes for time and random generation
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <sstream>

// ... inside RequestManager class
public:
    void send(const std::string &payload); // No change to signature
private:
    std::string generateTraceId(); // Add helper function
```

**File to edit: `src/core/RequestManager.cpp`**
```cpp
#include "core/RequestManager.h"
#include <iomanip> // for std::put_time

// Add this helper function inside the file or class
std::string RequestManager::generateTraceId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    
    std::stringstream ss;
    for (int i = 0; i < 16; ++i) {
        ss << std::hex << dis(gen);
    }
    return ss.str();
}

void RequestManager::send(const std::string &payload)
{
    // 1. Generate metadata
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::string timestamp = std::ctime(&now_c);
    timestamp.pop_back(); // Remove newline
    
    std::string traceId = generateTraceId();
    
    std::string logMessage = "TraceID: " + traceId + " | Timestamp: " + timestamp + " | Sending request: " + payload;

    // 2. Log the request with metadata
    Logger::instance().log(logMessage);

    // 3. Send the request via the adapter
    if (api_)
    {
        api_->sendRequest(payload);
    }

    // 4. Notify all observers (pass the metadata along)
    std::string notificationPayload = "TraceID: " + traceId + " | Payload: " + payload;
    for (IRequestObserver *obs : observers_)
    {
        obs->onRequestSent(notificationPayload);
    }
}
```

**Step 2: Update Observers**

The observers will now receive the payload with the trace ID. You can update them to parse and display this information.

**File to edit: `src/core/Observer.cpp`**
```cpp
void ConsoleObserver::onRequestSent(const std::string &payload)
{
    // Payload now includes TraceID
    std::cout << "[ConsoleObserver]: Received notification - " << payload << std::endl;
}
```

With these changes, your logs and notifications will be far more informative, making it easier to trace the lifecycle of each request.
