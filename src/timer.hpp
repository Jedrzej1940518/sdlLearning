
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

class Timer
{
private:
    bool active;
    std::unordered_map<std::string, float> funcTimes;
    std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> startTimes;

public:
    Timer(bool active) : active{active} {};

    void startTimer(const std::string &funcName)
    {
        if (not active)
            return;

        if (funcTimes.find(funcName) == funcTimes.end())
        {
            funcTimes[funcName] = 0.0f;
        }
        // Start the timer for the function
        startTimes[funcName] = std::chrono::high_resolution_clock::now();
    }

    void endTimer(const std::string &funcName)
    {
        if (not active)
            return;
        // Check if the function was registered and the timer was started
        if (startTimes.find(funcName) == startTimes.end())
        {
            std::cerr << "Timer for function " << funcName << " was not started." << std::endl;
            return;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - startTimes[funcName];
        funcTimes[funcName] += duration.count();
        startTimes.erase(funcName); // Remove the start time entry after stopping the timer
    }

    void writeResults(const std::string &fileName)
    {
        if (not active)
            return;

        std::ofstream outFile(fileName);
        if (outFile.is_open())
        {
            for (const auto &entry : funcTimes)
            {
                outFile << entry.first << ", " << entry.second << std::endl;
            }
            outFile.close();
        }
        else
        {
            std::cerr << "Unable to open file " << fileName << std::endl;
        }
    }
};