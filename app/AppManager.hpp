#pragma once

#include <string>
#include <vector>
#include <map>
#include "core/timer/Timer.hpp"

struct AppInfo 
{
    std::string name;
    Timer time;
};

class AppManager 
{
public:
    std::vector<AppInfo> apps;
    std::map<std::string, Timer> appTimers;

    bool ensureAppTimerExists(const std::string& name);
    void tickAppTimer(const std::string& name);
    std::string getAppTime(const std::string& name);
};