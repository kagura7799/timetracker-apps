#ifndef TIMETRACKERAPPS_H
#define TIMETRACKERAPPS_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>

class timetrackerapps : public QMainWindow
{
    Q_OBJECT;

public:
    timetrackerapps(QWidget* parent = nullptr);
    ~timetrackerapps();
    void addWindowItem(QString appName, QString time);
    void updateWindowTime(QString appName, QString newTime);
    bool containsApp(const QString& appName);

private slots:
    void setActiveWindowFilter();
    void setAllWindowFilter();

private:
    QPushButton* activeWindowsButton_;
    QPushButton* allWindowsButton_;
    QListWidget* windowListWidget_;
    bool activeFilter_ = true;
};
#endif // TIMETRACKERAPPS_H