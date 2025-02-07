#ifndef TIMETRACKERAPPS_H
#define TIMETRACKERAPPS_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>

class timetrackerapps : public QMainWindow
{
    Q_OBJECT

public:
    explicit timetrackerapps(QWidget* parent = nullptr);
    ~timetrackerapps();

    void addWindowItem(QString appName, QString time);
    void updateWindowTime(QString appName, QString newTime);
    void updateTotalTimeLabel(const QString& value);
    bool containsApp(const QString& appName);

private slots:
    void setActiveWindowFilter();
    void setAllWindowFilter();

private:
    QPushButton* activeWindowsButton_;
    QPushButton* allWindowsButton_;
    QListWidget* windowListWidget_;
    QPushButton* totalTimeValue;
};
#endif // TIMETRACKERAPPS_H