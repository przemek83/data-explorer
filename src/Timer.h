#pragma once

#include <chrono>

#include "Logger.h"

template <typename T>
class Timer
{
public:
    Timer() = default;
    ~Timer()
    {
        const std::chrono::time_point end{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> duration{end - start_};
        const auto executionTime{
            std::chrono::duration_cast<T>(duration).count()};
        Logger().logMsg("Execution time: " + std::to_string(executionTime) +
                        suffix_);
    }

    Timer(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer& operator=(Timer&&) = delete;

private:
    std::string getSuffix() const
    {
        if (std::is_same_v<T, std::chrono::hours>)
            return "h";
        else if (std::is_same_v<T, std::chrono::minutes>)
            return "min";
        else if (std::is_same_v<T, std::chrono::seconds>)
            return "s";
        else if (std::is_same_v<T, std::chrono::milliseconds>)
            return "ms";
        else if (std::is_same_v<T, std::chrono::microseconds>)
            return "us";
        else
            return "ns";
    }

    const std::string suffix_{getSuffix()};

    const std::chrono::time_point<std::chrono::steady_clock> start_{
        std::chrono::steady_clock::now()};
};
