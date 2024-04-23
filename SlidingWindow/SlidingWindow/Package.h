#pragma once
#include <string>

class Package
{
public:
	Package();

	std::string GetName() const;
	bool IsReceived() const;
	bool IsSent() const;

	void Receive();
	void Send();

	static std::string GetDefaultName();
private:
	const std::string m_name;
	bool m_received;
	bool m_sent;
	static uint16_t sPackageCounter;
};

