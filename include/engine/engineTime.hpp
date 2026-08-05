#ifndef ENGINETIME_HPP
#define ENGINETIME_HPP
#include <chrono>
#include <iostream>

class EngineTime{
    private:
        const std::chrono::time_point<std::chrono::steady_clock> _initTime;
        
    public:
        EngineTime(): _initTime(std::chrono::steady_clock::now()){};
        ~EngineTime() = default;
        EngineTime(const EngineTime& other) = delete;
        EngineTime(EngineTime&& other) noexcept = delete;
        EngineTime& operator=(const EngineTime& other) = delete;
        EngineTime& operator=(EngineTime&& other) noexcept = delete;

        double GetTimePassedInMilli(){
            auto now = std::chrono::steady_clock::now();
            return std::chrono::duration<double, std::milli>(now - _initTime).count();
        }
};
#endif