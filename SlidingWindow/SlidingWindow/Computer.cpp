#include "Computer.h"
#include "SlidingWindow.h"
#include "Timer.h"
#include "Random.h"
#include "Logger.h"

#include <thread>

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
        SendLoop(destination, window[window.GetStartWindowIndex()]);
        std::this_thread::sleep_for(3s);
        window.Slide();
    }
}

void Computer::SendLoop(Computer& destination, Package& package)
{
    static const uint16_t timeoutSeconds = 4;
    Timer timer(4);
    timer.Start();
    Send(destination, package);

    while (true)
    {
        if (package.IsReceived())
        {
            std::this_thread::sleep_for(1s);
            Logger::Log("source: acknowledgement for", package.GetName(), '!');
            return;
        }

        if (timer.ReachedThreshold())
        {
            Logger::Log(package.GetName(), "timed out");
            timer.Start();
            Send(destination, package);
        }

        std::this_thread::sleep_for(1s);
    }
}

void Computer::Send(Computer& destination, Package& package)
{
    Logger::Log("source ->", package.GetName());
    
    int chanceOfCorruption = Random::GetRandom(0, 5);
    if (chanceOfCorruption != 0)
    {
        std::thread thread(&Computer::Receive, &destination, std::ref(package));
        thread.detach();
    }
    else
        Logger::Log(package.GetName(), ": corrupted");
    
}

void Computer::Receive(Package& package)
{
    std::this_thread::sleep_for(2s);
    Logger::Log("destination: received", package.GetName(), '!');

    int chanceOfCorruption = Random::GetRandom(0, 5);
    if (chanceOfCorruption != 0)
        package.SetReceived(true);
    else
        Logger::Log(package.GetName(), ": acknowledgement corrupted");
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