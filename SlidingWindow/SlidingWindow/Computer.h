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
	void Receive(Computer& source, Package& package);
	//void Process

	static std::string GetDefaultName();
private:
	const std::string kName;
	std::vector<Package> receivedPackages;

private:
	static int sCounter;
};
std::ostream& operator<<(std::ostream& os, const Computer& c);