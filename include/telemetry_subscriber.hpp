#include "mocknats_client.hpp"
#include "telemetry.pb.h"
#include <string>

class TelemetrySubscriber {
public:
    TelemetrySubscriber(MockNatsClient& server, MockNatsClient::callback handler)
    {
        server.subscribe("sensor.temperature", [handler](const std::string& raw) {
            Telemetry msg;
            msg.ParseFromString(raw);
            handler(msg.SerializeAsString()); // or call a different handler
        });
    }
};