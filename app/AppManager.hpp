#ifndef APPMANAGER_HPP
#define APPMANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

#include "core/timer/Timer.hpp"

class AppManager {
public:
    bool ensureAppTimerExists(const std::string& name);
    void switchApp(const std::string& newApp);
    int getAppTime(const std::string& name);
    void sortApps();

    void saveHistoryToJson(const QString& filename);
    void loadHistoryFromJson(const QString& filename);

    const std::vector<std::pair<int, std::string>>& getSortedAppsVector();
    std::map<std::string, Timer>& getAppTimers();

    std::string currentApp;

private:
    std::map<std::string, Timer> appTimers;
    std::vector<std::pair<int, std::string>> sortedApps;

public:
    struct AppHistoryEntry {
        std::string appName;
        int timeInSeconds;
    };

    std::vector<AppHistoryEntry> appHistory;
};

#endif