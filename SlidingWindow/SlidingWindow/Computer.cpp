#include "Computer.h"
#include "SlidingWindow.h"
#include "Timer.h"
#include "Random.h"
#include "Logger.h"

#include <thread>
#include <algorithm>

uint16_t Computer::sCounter = 0;

Computer::Computer() :
    kName{ GetDefaultName() + std::to_string(sCounter) }
{
    sCounter++;
}
std::string Computer::GetName() const
{
    return kName;
}

void Computer::SendPackages(Computer& destination, uint16_t noOfPackages)
{
    SlidingWindow window(noOfPackages);

    while (!window.AllPackagesSent())
    {
        std::vector<size_t> packages{ std::move(window.GetUnsentIndices()) };
        if (!packages.size())
            return;
        std::vector<std::thread> threads;
        std::ranges::for_each(packages, [&](const size_t& index)
            {
                std::this_thread::sleep_for(0.3s);
                std::thread thread([&]() {
                    destination.Send(destination, window[index]);
                    });

                threads.push_back(std::move(thread));
            });

        std::ranges::for_each(threads, [](std::thread& thread)
            {
                thread.join();
                //std::this_thread::sleep_for(1s);
            });
        //std::this_thread::sleep_for(4s);
        window.Slide();
    }
    destination.ShowReceivedPackages();
}

void Computer::Send(Computer& destination, Package& package)
{
    static const uint16_t timeoutSeconds = 4;

    package.SetSent(true);

    Logger::Log("source ->", package.GetName());

    int chanceOfCorruption = Random::GetRandom(0, 6);
    if (chanceOfCorruption != 0)
        destination.Receive(package);
    else
        Logger::Log(package.GetName(), ": corrupted");

    if (package.IsReceived())
    {
        Logger::Log("source: acknowledgement for", package.GetName(), '!');
        return;
    }
    std::this_thread::sleep_for(3s);
    Logger::Log(package.GetName(), "timed out");
    package.SetSent(false);
}

void Computer::Receive(Package& package)
{
    std::this_thread::sleep_for(3s);
    
    if (HasReceived(package))
        Logger::Log("destination: received and ignored", package.GetName());
    else
    {
        Logger::Log("destination: received", package.GetName(), '!');
        m_receivedPackages.push_back(package);
    }

    std::this_thread::sleep_for(3s);

    int chanceOfCorruption = Random::GetRandom(0, 6);
    if (chanceOfCorruption != 0)
        package.Receive();
    else
        Logger::Log(package.GetName(), ": acknowledgement corrupted");
}

bool Computer::HasReceived(const Package& package) const
{
    for (size_t i = 0; i < m_receivedPackages.size(); i++)
    {
        if (m_receivedPackages[i].GetName() == package.GetName())
            return true;
    }
    return false;
}

void Computer::ShowReceivedPackages()
{
    std::sort(m_receivedPackages.begin(), m_receivedPackages.end());
    std::cout << "\n packages received:\n ";
    std::ranges::for_each(m_receivedPackages, [](const Package& pckg) {std::cout << pckg.GetName() << "\n "; });
}

void Computer::SortPackages()
{
    //std::sort(m_receivedPackages.begin(), m_receivedPackages.end());
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