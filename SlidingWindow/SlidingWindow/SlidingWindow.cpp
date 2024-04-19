#include "SlidingWindow.h"

#include<stdexcept>

SlidingWindow::SlidingWindow(uint16_t noOfPackages):
	kWindowSize{ 3 },
	m_startOfWindow{ 0 }
{
	for (int i = 0; i < noOfPackages; i++)
		m_packagesToSend.push_back({});
}

size_t SlidingWindow::GetStartWindowIndex() const
{
	return m_startOfWindow;
}

void SlidingWindow::SetStartWindowIndex(size_t index)
{
	m_startOfWindow = index;
}

size_t SlidingWindow::size() const
{
	return m_packagesToSend.size();
}

Package& SlidingWindow::operator[](size_t index)
{
	if (index < 0 or index >= m_packagesToSend.size())
		throw std::out_of_range("Index out of range");

	return m_packagesToSend[index];
}

bool SlidingWindow::AllPackagesSent() const
{
	return m_startOfWindow == m_packagesToSend.size();
}
void SlidingWindow::Slide()
{
	while (!AllPackagesSent() and m_packagesToSend[m_startOfWindow].IsReceived())
		m_startOfWindow++;
}
