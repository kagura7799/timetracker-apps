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

private slots:
    void setActiveWindowFilter();
    void setAllWindowFilter();

private:
    QPushButton* activeWindowsButton_;
    QPushButton* allWindowsButton_;
    QListWidget* windowListWidget_;
    bool activeFilter_ = true;
    void addWindowItem(const QString& appName, const QString& time);
    void updateWindowList();
};
#endif // TIMETRACKERAPPS_H