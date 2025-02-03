#include "gui\timetrackerapps.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    timetrackerapps w;
    w.show();
    return a.exec();
}