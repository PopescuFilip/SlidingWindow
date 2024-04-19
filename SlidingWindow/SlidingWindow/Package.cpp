#include "Package.h"

uint16_t Package::sPackageCounter = 1;

Package::Package():
	m_name{ GetDefaultName() + std::to_string(sPackageCounter)},
	m_received{ false }
{
	sPackageCounter++;
}

std::string Package::GetName() const
{
	return m_name;
}

bool Package::IsReceived() const
{
	return m_received;
}

void Package::SetReceived(bool received)
{
	m_received = received;
}

std::string Package::GetDefaultName()
{
	return "package";
}
