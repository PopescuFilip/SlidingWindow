#pragma once
#include "Package.h"

#include <vector>

class SlidingWindow
{
public:
	SlidingWindow(uint16_t noOfPackages);

	size_t GetStartWindowIndex() const;

	void SetStartWindowIndex(size_t index);

	size_t size() const;
	Package& operator[](size_t index);

	bool AllPackagesSent() const;
	void Slide();
private:
	std::vector<Package> m_packagesToSend;
	size_t m_startOfWindow;

	const uint16_t kWindowSize;
};

