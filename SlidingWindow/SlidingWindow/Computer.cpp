#include "Computer.h"
#include "SlidingWindow.h"
#include "Timer.h"
#include "Random.h"

#include <thread>
#include <iostream>

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
        Send(destination, window[window.GetStartWindowIndex()]);
        window.Slide();
    }
}

void Computer::Send(Computer& destination, Package& package)
{
    static const uint16_t timeoutSeconds = 4;
    Timer timer(4);
    timer.Start();

    std::thread thread(&Computer::Receive, &destination, std::ref(package));
    thread.detach();

    while (true)
    {
        if (package.IsReceived())
        {
            std::this_thread::sleep_for(1s);
            std::cout << "source: received acknowledgement for " << package.GetName() << '\n';
            return;
        }

        if (timer.ReachedThreshold())
        {
            std::cout << package.GetName() << " timed out\n";
            timer.Start();
            std::thread thread(&Computer::Receive, &destination, std::ref(package));
            thread.detach();
        }

        std::this_thread::sleep_for(1s);
    }
}

void Computer::Receive(Package& package)
{
    std::this_thread::sleep_for(2s);
    std::cout << "destination: received " << package.GetName() << '\n';

    int chanceOfCorruption = Random::GetRandom(0, 4);
    if (chanceOfCorruption != 0)
        package.SetReceived(true);
    else
        std::cout << "acknowledgement corrupted";
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