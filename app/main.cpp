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
    timetrackerapps w;

    AppManager appManager;
    ActiveWindowTracker winTracker(appManager);
    TotalTime totalTime;

    QTimer* timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&, w_ptr = &w]() {
        winTracker.updateListApps(w_ptr);
        totalTime.TotalTimeTicker(w_ptr);
    });

    timer->start(1000);

    w.show();
    return a.exec();
}