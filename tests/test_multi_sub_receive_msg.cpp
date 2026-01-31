#include <catch2/catch_test_macros.hpp>
#include "mocknats_client.hpp"

TEST_CASE("Multi‑subscriber message delivery", "[multi_sub_receive_msg]") {

    MockNatsClient mockClient;

    SECTION("Client connects successfully") {
        REQUIRE(mockClient.connect("nats://localhost:4222") == true);
        REQUIRE(mockClient.isConnected() == true);
    }

    SECTION("Multiple subscribers receive the same published message") {
        mockClient.connect("nats://localhost:4222");

        std::string receivedMsg1;
        std::string receivedMsg2;
        int callbackCount = 0;

        SECTION("Register two subscribers") {
            mockClient.subscribe("test.subject", [&](const std::string& msg) {
                receivedMsg1 = msg;
                callbackCount++;
            });

            mockClient.subscribe("test.subject", [&](const std::string& msg) {
                receivedMsg2 = msg;
                callbackCount++;
            });
        }

        SECTION("Publish triggers both callbacks") {
            mockClient.subscribe("test.subject", [&](const std::string& msg) {
                receivedMsg1 = msg;
                callbackCount++;
            });

            mockClient.subscribe("test.subject", [&](const std::string& msg) {
                receivedMsg2 = msg;
                callbackCount++;
            });

            REQUIRE(mockClient.publish("test.subject", "Hello, World!") == true);

            REQUIRE(receivedMsg1 == "Hello, World!");
            REQUIRE(receivedMsg2 == "Hello, World!");
            REQUIRE(callbackCount == 2);
        }
    }

    SECTION("Client disconnects successfully") {
        mockClient.connect("nats://localhost:4222");
        mockClient.disconnect();
        REQUIRE(mockClient.isConnected() == false);
    }
}
