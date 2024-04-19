#include "SlidingWindow.h"

SlidingWindow::SlidingWindow(uint16_t noOfPackages):
	m_windowSize{ 3 }
{
	for (int i = 0; i < noOfPackages; i++)
		m_packagesToSend.push_back({});
}
