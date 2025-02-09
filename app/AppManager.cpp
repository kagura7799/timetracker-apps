#include "AppManager.hpp"

bool AppManager::ensureAppTimerExists(const std::string& name)
{
    if (appTimers.find(name) != appTimers.end())
        return false;

    appTimers[name] = Timer();
    return true;
}

void AppManager::switchApp(const std::string& newApp) {
    if (!currentApp.empty() && appTimers.find(currentApp) != appTimers.end()) {
        appTimers[currentApp].stop();
    }

    currentApp = newApp;
    ensureAppTimerExists(newApp);
    appTimers[newApp].start();
}

int AppManager::getAppTime(const std::string& name)
{
    if (appTimers.find(name) != appTimers.end())
        return appTimers[name].getTimeInSeconds();
    return 0;
}

void AppManager::sortApps()
{
    sortedApps.clear();

    for (const auto& [appName, timer] : appTimers)
    {
        sortedApps.emplace_back(timer.getTimeInSeconds(), appName);
    }

    std::sort(sortedApps.rbegin(), sortedApps.rend());
}

const std::vector<std::pair<int, std::string>>& AppManager::getSortedAppsVector() 
{
    return sortedApps;
}

std::map<std::string, Timer>& AppManager::getAppTimers()
{
    return appTimers;
}
