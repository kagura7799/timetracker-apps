#ifndef TIMETRACKERAPPS_H
#define TIMETRACKERAPPS_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QColor>
#include <QSpacerItem>
#include "app/AppManager.hpp"

class timetrackerapps : public QMainWindow
{
    Q_OBJECT

public:
    timetrackerapps(AppManager& manager, QWidget* parent = nullptr);
    ~timetrackerapps() override;

public slots:
    void addWindowItem(QString appName, QString time);
    void updateWindowTime(QString appName, QString newTime);
    bool containsApp(const QString& appName);
    void updateTotalTimeLabel(const QString& value);
    void updateList();

private:
    QListWidget* windowListWidget_;
    QPushButton* totalTimeValue;

    AppManager& manager;

    QColor zebraColor1_;
    QColor zebraColor2_;
};

#endif