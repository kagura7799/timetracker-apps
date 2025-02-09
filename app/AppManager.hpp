#ifndef APPMANAGER_HPP
#define APPMANAGER_HPP

#include "core/timer/Timer.hpp"
#include <map>
#include <vector>
#include <string>
#include <algorithm>

class AppManager {
public:
    bool ensureAppTimerExists(const std::string& name);
    void switchApp(const std::string& newApp);
    int getAppTime(const std::string& name);
    void sortApps();
    const std::vector<std::pair<int, std::string>>& getSortedAppsVector();
    std::map<std::string, Timer>& getAppTimers();

private:
    std::map<std::string, Timer> appTimers;
    std::vector<std::pair<int, std::string>> sortedApps;
    std::string currentApp;
};

#endif // APPMANAGER_HPP
