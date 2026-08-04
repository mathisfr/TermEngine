#ifndef ENGINETIME_HPP
#define ENGINETIME_HPP
#include <chrono>
#include <iostream>

class EngineTime{
    private:
        const std::chrono::time_point<std::chrono::steady_clock> _initTime;
        
    public:
        EngineTime(): _initTime(std::chrono::steady_clock::now()){

        };

        double GetTimePassedInMilli(){
            auto now = std::chrono::steady_clock::now();
            return std::chrono::duration<double, std::milli>(now - _initTime).count();
        }
};
#endif