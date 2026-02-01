#include <catch2/catch_test_macros.hpp>
#include "mocknats_client.hpp"
#include "telemetry.pb.h"
#include "telemetry_msg_processor.hpp"
#include "telemetry_publisher.hpp"
#include "telemetry_subscriber.hpp"


TEST_CASE("Telemetry pub/sub end-to-end", "[telemetry][pubsub][nats]") {
    MockNatsClient server;

    REQUIRE(server.connect("nats://localhost:4222") == true);
    REQUIRE(server.isConnected() == true);

    TelemetryPublisher publisher(server);
    TelemetryMessageProcessor processor;

    bool received1 = false; 
    bool received2 = false; 
    TelemetryResult result1; 
    TelemetryResult result2;

    // Subscriber: receives protobuf → processes it
    TelemetrySubscriber sub1(server, [&](const std::string& raw) {
        Telemetry msg;
        msg.ParseFromString(raw);
        result1 = processor.process(msg);
        received1 = true;
    });

    TelemetrySubscriber sub2(server, [&](const std::string& raw) {
        Telemetry msg;
        msg.ParseFromString(raw);
        result2 = processor.process(msg);
        received2 = true;
    });


    // Build telemetry message
    Telemetry msg;
    msg.set_id(101);
    msg.set_temp(100.0);


    // Publish
    publisher.publishTelemetry("sensor.temperature", msg);

    // Assertions
    REQUIRE(received1); 
    REQUIRE(received2);
    REQUIRE(result1.ok);
    REQUIRE(result2.ok);

    double expectedRiskIndex = 1.0; // since temperature is 100
    REQUIRE(result1.processed_risk_index == expectedRiskIndex);
    REQUIRE(result2.processed_risk_index == expectedRiskIndex);

    SECTION("Client disconnects successfully") {
        server.connect("nats://localhost:4222");
        server.disconnect();
        REQUIRE(server.isConnected() == false);
    }
}

