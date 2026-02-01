#pragma once
#include "nats_client.hpp"
#include <vector>
#include <string>

class MockNatsClient : public NatsClient {
public:
    bool connect(const std::string& url) override {
        // Mock implementation of connect
        bIsConnected = true;
        return bIsConnected;
    }
    
    void disconnect() override {
        // Mock implementation of disconnect
        bIsConnected = false;        
    }

    bool isConnected() const override {
        return bIsConnected;
    }   

    bool publish(const std::string& subject, const std::string& message) override {
        // Mock implementation of publish
        publishedMessages.push_back("Subject: " + subject + ", Message: " + message);
        for (const auto& sub : subscriptions) {
            if (sub.first == subject) {
                sub.second(message); // Call the callback - simulate message delivery
            }
        }
        return true;
    }

    bool subscribe(const std::string& subject, callback cb) override {
        // Mock implementation of subscribe
        subscriptions.emplace_back(subject, cb); // store multiple callbacks
        return true;
    }

private:
    bool bIsConnected = false;
    std::vector<std::pair<std::string, callback>> subscriptions;
    std::vector<std::string> publishedMessages;
};