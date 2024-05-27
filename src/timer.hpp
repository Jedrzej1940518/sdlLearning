
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

class Timer
{
private:
    bool active;
    std::unordered_map<std::string, float> funcTimes;

public:
    Timer(bool active) : active{active} {};

    void registerFunc(const std::string &funcName)
    {
        if (not active)
            return;

        if (funcTimes.find(funcName) == funcTimes.end())
        {
            funcTimes[funcName] = 0.0f;
        }
    }

    void addTime(const std::string &funcName, float time)
    {
        if (not active)
            return;

        if (funcTimes.find(funcName) != funcTimes.end())
        {
            funcTimes[funcName] += time;
        }
        else
        {
            std::cerr << "Function " << funcName << " is not registered." << std::endl;
        }
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