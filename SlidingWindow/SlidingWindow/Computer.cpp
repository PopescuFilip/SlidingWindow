#include "Computer.h"
#include <sstream>

int Computer::sCounter = 0;

Computer::Computer() :
    kName{ GetDefaultName() + std::to_string(sCounter) }
{
    sCounter++;
}
std::string Computer::GetName() const
{
    return kName;
}

std::string Computer::GetDefaultName()
{
    return "computer";
}

std::ostream& operator<<(std::ostream& os, const Computer& c)
{
    os << c.GetName();
    return os;
}