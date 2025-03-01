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

void AppManager::saveHistoryToJson(const QString& filename) 
{
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataLocation);
    QString fullFilePath = appDataLocation + "/" + filename;

    QJsonArray jsonArray;
    for (const auto& [appName, timer] : appTimers)
    {
        QJsonObject jsonObject;
        jsonObject["AppName"] = QString::fromStdString(appName);
        jsonObject["TimeInSeconds"] = timer.getElapsedSeconds();
        jsonArray.append(jsonObject);
    }

    QJsonDocument jsonDocument(jsonArray);
    QFile jsonFile(fullFilePath);
    if (jsonFile.open(QIODevice::WriteOnly))
    {
        jsonFile.write(jsonDocument.toJson());
        jsonFile.close();
    }
    else 
    {
        qDebug() << "Failed to open file for write: " << fullFilePath;
    }
}

void AppManager::loadHistoryFromJson(const QString& filename) 
{
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString fullFilePath = appDataLocation + "/" + filename;
    QFile jsonFile(fullFilePath);

    if (!jsonFile.open(QIODevice::ReadOnly)) 
    {
        qDebug() << "Failed to open file for read: " << fullFilePath;
        return;
    }

    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    if (!jsonDocument.isArray()) 
    {
        qDebug() << "Invalid JSON format";
        return;
    }

    QJsonArray jsonArray = jsonDocument.array();
    for (const QJsonValue& value : jsonArray) {
        if (!value.isObject()) continue;
        QJsonObject jsonObject = value.toObject();

        std::string appName = jsonObject["AppName"].toString().toStdString();
        int timeInSeconds = jsonObject["TimeInSeconds"].toInt();

        appTimers[appName].setElapsedSeconds(timeInSeconds);
    }
}

const std::vector<std::pair<int, std::string>>& AppManager::getSortedAppsVector()
{
	return sortedApps;
}

std::map<std::string, Timer>& AppManager::getAppTimers()
{
	return appTimers;
}