#pragma once
#include "Package.h"

#include <vector>

class SlidingWindow
{
public:
	SlidingWindow(uint16_t noOfPackages);
private:
	std::vector<Package> m_packagesToSend;
	const uint16_t m_windowSize;
};

