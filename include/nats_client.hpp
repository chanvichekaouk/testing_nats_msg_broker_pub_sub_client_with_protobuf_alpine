// nats_client.hpp
#pragma once
#include <string>
#include <functional>

// pure abstract class
class NatsClient {
public:
	using callback = std::function<void(const std::string&)>; // this is just like func<> delegate in c#

	virtual ~NatsClient() = default;
	virtual bool connect(const std::string& url) = 0;
	virtual void disconnect() = 0;
	virtual bool isConnected() const = 0;
	virtual bool publish(const std::string& subject, const std::string& message) =	 0;
	virtual bool subscribe(const std::string& subject, callback cb) = 0;			
};
