#pragma once
#include <string>

class Package
{
public:
	Package();

	std::string GetName() const;
	bool IsReceived() const;

	void SetReceived(bool received);

	static std::string GetDefaultName();
private:
	const std::string m_name;
	bool m_received;
	static uint16_t sPackageCounter;
};

