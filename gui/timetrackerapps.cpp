#include "gui/timetrackerapps.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include <QFrame>
#include <QListWidgetItem>
#include <QDebug>
#include <QSpacerItem>

timetrackerapps::timetrackerapps(AppManager& manager, QWidget* parent)
    : QMainWindow(parent), manager(manager), zebraColor1_("#36393f"), zebraColor2_("#424549")
{
    setWindowTitle("TimeTracker");
    resize(600, 600); // Увеличим размер окна

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Title bar
    QHBoxLayout* titleBarLayout = new QHBoxLayout();
    QLabel* titleLabel = new QLabel("TimeTracker");
    titleLabel->setStyleSheet("font-size: 36px; color: white;"); // Увеличим размер шрифта
    titleBarLayout->addWidget(titleLabel);
    titleBarLayout->addStretch();
    mainLayout->addLayout(titleBarLayout);

    // Total time area
    QHBoxLayout* totalTimeLayout = new QHBoxLayout();
    QLabel* totalTimeLabel = new QLabel("Total time");
    totalTimeLabel->setStyleSheet("color: white;");
    totalTimeValue = new QPushButton();
    totalTimeValue->setStyleSheet("color: black; background-color: #559ad0; border-radius: 5px; padding: 5px 10px;");
    totalTimeValue->setEnabled(false);
    totalTimeLayout->addWidget(totalTimeLabel);
    totalTimeLayout->addStretch();
    totalTimeLayout->addWidget(totalTimeValue);

    QComboBox* timeRangeDropdown = new QComboBox();
    timeRangeDropdown->addItem("Day");
    timeRangeDropdown->addItem("Week");
    timeRangeDropdown->addItem("Month");
    timeRangeDropdown->addItem("Year");
    timeRangeDropdown->setStyleSheet("border: none; background-color: white; padding: 5px 10px; border-radius: 5px;");
    totalTimeLayout->addWidget(timeRangeDropdown);
    mainLayout->addLayout(totalTimeLayout);

    // Добавляем разделитель
    QSpacerItem* spacer = new QSpacerItem(1, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mainLayout->addItem(spacer);

    // Scrollable window list
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: #36393f; border: none;");

    windowListWidget_ = new QListWidget();
    windowListWidget_->setStyleSheet("background-color: #36393f; border: none;");
    scrollArea->setWidget(windowListWidget_);
    mainLayout->addWidget(scrollArea);
    mainLayout->addStretch();

    // Set background color of the main window
    setStyleSheet("background-color: #36393f;");
}

timetrackerapps::~timetrackerapps()
{
}

void timetrackerapps::addWindowItem(QString appName, QString time) {
    QListWidgetItem* item = new QListWidgetItem();

    QWidget* customWidget = new QWidget();
    QHBoxLayout* widgetLayout = new QHBoxLayout(customWidget);
    widgetLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* appNameLabel = new QLabel(appName);
    appNameLabel->setStyleSheet("color: white; font-size: 16px;");
    QLabel* timeLabel = new QLabel(time);
    timeLabel->setStyleSheet("color: white; font-size: 16px;");

    widgetLayout->addWidget(appNameLabel);
    widgetLayout->addStretch();
    widgetLayout->addWidget(timeLabel);
    customWidget->setLayout(widgetLayout);

    // Устанавливаем цвет фона для customWidget
    int row = windowListWidget_->row(item);
    if (row % 2 == 0) {
        customWidget->setStyleSheet(QString("background-color: %1;").arg(zebraColor1_.name()));
        item->setBackground(zebraColor1_);
    }
    else {
        customWidget->setStyleSheet(QString("background-color: %1;").arg(zebraColor2_.name()));
        item->setBackground(zebraColor2_);
    }

    item->setSizeHint(customWidget->sizeHint());
    windowListWidget_->addItem(item);
    windowListWidget_->setItemWidget(item, customWidget);
}

void timetrackerapps::updateWindowTime(QString appName, QString newTime) {
    for (int i = 0; i < windowListWidget_->count(); ++i) {
        QListWidgetItem* item = windowListWidget_->item(i);
        QWidget* customWidget = windowListWidget_->itemWidget(item);
        if (!customWidget) continue;

        QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(customWidget->layout());
        if (!layout) continue;

        QLabel* appNameLabel = nullptr;
        QLabel* timeLabel = nullptr;

        for (int j = 0; j < layout->count(); ++j) {
            QWidget* widget = layout->itemAt(j)->widget();
            if (!widget) continue;

            QLabel* label = qobject_cast<QLabel*>(widget);
            if (!label) continue;

            if (!appNameLabel) {
                appNameLabel = label;
            }
            else {
                timeLabel = label;
                break;
            }
        }

        if (appNameLabel && timeLabel && appNameLabel->text() == appName) {
            timeLabel->setText(newTime);
            break;
        }
    }
}

bool timetrackerapps::containsApp(const QString& appName)
{
    for (int i = 0; i < windowListWidget_->count(); ++i) {
        QListWidgetItem* item = windowListWidget_->item(i);
        QWidget* customWidget = windowListWidget_->itemWidget(item);
        if (!customWidget)
            continue;

        QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(customWidget->layout());
        if (!layout)
            continue;

        QLabel* appNameLabel = qobject_cast<QLabel*>(layout->itemAt(0)->widget());
        if (appNameLabel && appNameLabel->text() == appName)
            return true;
    }
    return false;
}

void timetrackerapps::updateTotalTimeLabel(const QString& value)
{
    totalTimeValue->setText(value);
}

void timetrackerapps::updateList()
{
    manager.sortApps();
    windowListWidget_->clear();

    for (const auto& [time, appName] : manager.getSortedAppsVector())
    {
        if (!containsApp(QString::fromStdString(appName)))
            addWindowItem(QString::fromStdString(appName), QString::fromStdString(manager.getAppTimers()[appName].getTimeFormatted(time)));
    }
}