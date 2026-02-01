
#include "mocknats_client.hpp"
#include "telemetry.pb.h"
#include <string>

class TelemetryPublisher {
public:
    TelemetryPublisher(MockNatsClient& nats_server)
        : _nats_server(nats_server) {}

    bool publishTelemetry(const std::string& subject, const Telemetry& message) {
        if (!_nats_server.isConnected()) {
            return false;
        }

        std::string serializedMessage;
        if (!message.SerializeToString(&serializedMessage)) {
            return false;
        }

        return _nats_server.publish(subject, serializedMessage);
    }

private:
    MockNatsClient& _nats_server;

};