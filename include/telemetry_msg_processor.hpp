#include "mocknats_client.hpp"
#include "telemetry.pb.h"

struct TelemetryResult {
    bool ok;
    int32_t id;
    double processed_risk_index;
};

class TelemetryMessageProcessor {
public:
    TelemetryResult process(const Telemetry& msg) {
        double processed_risk_index = msg.temp() >= 100 ? 1.0 : 0.0;
        return {true, msg.id(), processed_risk_index};
    }
};