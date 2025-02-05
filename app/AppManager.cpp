#include "AppManager.hpp"
#include "core/timer/Timer.hpp"

bool AppManager::ensureAppTimerExists(const std::string& name)
{
    if (appTimers.find(name) != appTimers.end()) 
        return false;

    apps.push_back({ name, Timer() });
    appTimers[name] = Timer();
    return true;
}

void AppManager::tickAppTimer(const std::string& name)
{
    if (appTimers.find(name) != appTimers.end()) 
        appTimers[name].tick();
}

std::string AppManager::getAppTime(const std::string& name) 
{
    if (appTimers.find(name) != appTimers.end()) 
        return appTimers[name].currentTime();

    return "0 h. 0 min. 0 sec";
}
