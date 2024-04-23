#include "Package.h"

uint16_t Package::sPackageCounter = 1;

Package::Package():
	m_name{ GetDefaultName() + std::to_string(sPackageCounter)},
	m_received{ false },
	m_sent{ false }
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

bool Package::IsSent() const
{
	return false;
}

void Package::Receive()
{
	m_received = true;
}

void Package::Send()
{
	m_sent = true;
}

std::string Package::GetDefaultName()
{
	return "package";
}
