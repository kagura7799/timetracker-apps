#ifndef TIMETRACKERAPPS_H
#define TIMETRACKERAPPS_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include "app/AppManager.hpp"

class timetrackerapps : public QMainWindow
{
    Q_OBJECT

public:
    explicit timetrackerapps(AppManager& manager, QWidget* parent = nullptr);
    ~timetrackerapps();

    void addWindowItem(QString appName, QString time);
    void updateWindowTime(QString appName, QString newTime);
    void updateTotalTimeLabel(const QString& value);
    bool containsApp(const QString& appName);
    void updateList();


private slots:
    void setActiveWindowFilter();
    void setAllWindowFilter();

private:
    QPushButton* activeWindowsButton_;
    QPushButton* allWindowsButton_;
    QListWidget* windowListWidget_;
    QPushButton* totalTimeValue;
    AppManager&  manager;
};
#endif // TIMETRACKERAPPS_H