#include "gui/timetrackerapps.h"
#include "core/tracking/ActiveWindowTracker.hpp"
#include "app/AppManager.hpp"
#include "core/calculator/TotalTime.hpp"
#include <QApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    AppManager appManager;

    appManager.loadHistoryFromJson("timetrackerappsData.json");

    timetrackerapps w(appManager);

    ActiveWindowTracker winTracker(appManager);
    TotalTime totalTime(appManager);

    QTimer* timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&, w_ptr = &w]() {
        winTracker.updateListApps(w_ptr);
        totalTime.TotalTimer(w_ptr);
    });

    timer->start(1000);

    w.show();
    return a.exec();
}

