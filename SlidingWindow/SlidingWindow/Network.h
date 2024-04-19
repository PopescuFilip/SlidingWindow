#pragma once
#include "Computer.h"

class Network
{
public:
	static void SendPackages(Computer& source, Computer& destination, uint16_t noOfPackages);
};

