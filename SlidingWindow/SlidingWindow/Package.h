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
	void SetSent(bool sent);

	static std::string GetDefaultName();

	bool operator <(const Package& other) const;
	bool operator ==(const Package& other) const;
private:
	uint16_t m_number;
	bool m_received;
	bool m_sent;
	static uint16_t sPackageCounter;
};

