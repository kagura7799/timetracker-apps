#include "TotalTime.hpp"

TotalTime::TotalTime(AppManager& appManager) : appManager_(appManager)
{
	timer.start();
}

void TotalTime::TotalTimer(timetrackerapps* window)
{
    int totalTime = 0;
    for (const auto& [appName, timer] : appManager_.getAppTimers()) {
        totalTime += timer.getTimeInSeconds();
    }

    std::string currentTime = timer.getTimeFormatted(totalTime);
    presenter.updateTotalTimeLabel(window, QString::fromStdString(currentTime));
}

