#include "Network.h"


void Network::SendPackages(Computer& source, Computer& destination, uint16_t noOfPackages)
{
	source.SendPackages(destination, noOfPackages);
}
