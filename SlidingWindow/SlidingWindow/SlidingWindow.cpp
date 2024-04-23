#include "SlidingWindow.h"

#include<stdexcept>

SlidingWindow::SlidingWindow(uint16_t noOfPackages):
	m_windowSize{ static_cast<uint16_t>(noOfPackages / 2) },
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

std::vector<size_t> SlidingWindow::GetUnsentIndices() const
{
	if (AllPackagesSent())
		return std::vector<size_t>();
	std::vector<size_t> packages;
	for (size_t i = 0; i < m_windowSize && m_startOfWindow + i < m_packagesToSend.size(); i++)
		if (Package package = m_packagesToSend[m_startOfWindow + i]; !package.IsSent())
		{
			//Logger::Log(package.GetName(), "not sent");
			packages.push_back(m_startOfWindow + i);
		}
	return packages;
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
