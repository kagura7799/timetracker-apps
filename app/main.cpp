#include "gui/timetrackerapps.h"
#include "core/tracking/ActiveWindowTracker.hpp"
#include <QApplication>
#include "QDebug"
#include <QTimer>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    timetrackerapps w;

    ActiveWindowTracker winTracker;

    QTimer* timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&, w_ptr = &w]() {
        winTracker.trackActiveWindowTime(w_ptr);
    });

    timer->start(1000);

    w.show();
    return a.exec();
}