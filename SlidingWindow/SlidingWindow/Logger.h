#include <mutex>
#include <iostream>

class Logger
{
public:
    template <typename... Args>
    static void Log(Args&&... args)
    {
        std::lock_guard lockCout{ m_mutexCout };
        ((std::cout << ' ' << std::forward<Args>(args)), ...);

        std::cout << '\n';
    }

private:
    inline static std::mutex m_mutexCout;
};