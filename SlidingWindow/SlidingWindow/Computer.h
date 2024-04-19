#pragma once
#include "Package.h"

#include <string>
#include <vector>

class Computer
{
public:

	Computer();

	std::string GetName() const;

	void SendPackages(Computer& destination, uint16_t noOfPackages);
	void Send(Computer& destination, Package& package);
	void Receive(Package& package);
	//void Process

	static std::string GetDefaultName();
private:
	const std::string kName;
	std::vector<Package> receivedPackages;

private:
	static uint16_t sCounter;
};
std::ostream& operator<<(std::ostream& os, const Computer& c);