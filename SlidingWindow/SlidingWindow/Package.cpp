#include "Package.h"

uint16_t Package::sPackageCounter = 1;

Package::Package():
	m_number{ sPackageCounter },
	m_received{ false },
	m_sent{ false }
{
	sPackageCounter++;
}

std::string Package::GetName() const
{
	return GetDefaultName() + std::to_string(m_number);
}

bool Package::IsReceived() const
{
	return m_received;
}

bool Package::IsSent() const
{
	return m_sent;
}

void Package::Receive()
{
	m_received = true;
}

void Package::SetSent(bool sent)
{
	m_sent = sent;
}

std::string Package::GetDefaultName()
{
	return "package";
}

bool Package::operator<(const Package& other) const
{
	return this->m_number < other.m_number;
}

bool Package::operator==(const Package& other) const
{
	return this->m_number == other.m_number;
}
