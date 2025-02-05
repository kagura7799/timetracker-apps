#include "gui/timetrackerapps.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include <QFrame>
#include <QListWidgetItem>
#include <QDebug>

timetrackerapps::timetrackerapps(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("TimeTracker");
    resize(400, 400);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Title bar with close button
    QHBoxLayout* titleBarLayout = new QHBoxLayout();
    QLabel* titleLabel = new QLabel("TimeTracker");
    titleLabel->setStyleSheet("font-size: 22px;");
    titleLabel->setStyleSheet("color: white;");
    titleBarLayout->addWidget(titleLabel);
    titleBarLayout->addStretch();
    mainLayout->addLayout(titleBarLayout);

    // Total time area
    QHBoxLayout* totalTimeLayout = new QHBoxLayout();
    QLabel* totalTimeLabel = new QLabel("Total time");
    totalTimeLabel->setStyleSheet("color: white;");
    QPushButton* totalTimeValue = new QPushButton("7 h. 20 min.");
    totalTimeValue->setStyleSheet("color: black; background-color: #559ad0; border-radius: 5px; padding: 5px 10px;");
    totalTimeValue->setEnabled(false); // Disable clickability
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


    // Buttons for active/all windows
    QHBoxLayout* filterButtonsLayout = new QHBoxLayout();
    activeWindowsButton_ = new QPushButton("Only active windows");
    activeWindowsButton_->setStyleSheet("background-color: #559ad0; color: white; border: none; padding: 5px 10px; border-radius: 5px;");
    connect(activeWindowsButton_, &QPushButton::clicked, this, &timetrackerapps::setActiveWindowFilter);

    allWindowsButton_ = new QPushButton("All opened windows");
    allWindowsButton_->setStyleSheet("background-color: #e0e0e0; color: black; border: none; padding: 5px 10px; border-radius: 5px;");
    connect(allWindowsButton_, &QPushButton::clicked, this, &timetrackerapps::setAllWindowFilter);

    filterButtonsLayout->addWidget(activeWindowsButton_);
    filterButtonsLayout->addWidget(allWindowsButton_);
    mainLayout->addLayout(filterButtonsLayout);


    // Scrollable window list
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: #36393f;");


    windowListWidget_ = new QListWidget();
    windowListWidget_->setStyleSheet("background-color: #36393f; border: none;");
    scrollArea->setWidget(windowListWidget_);


    mainLayout->addWidget(scrollArea);
    mainLayout->addStretch();


    // Set background color of the main window
    setStyleSheet("background-color: #36393f;");


    // Initialize default filter: active windows
    setActiveWindowFilter();
}

timetrackerapps::~timetrackerapps()
{
}

void timetrackerapps::setActiveWindowFilter()
{
    activeWindowsButton_->setStyleSheet("background-color: #559ad0; color: white; border: none; padding: 5px 10px; border-radius: 5px;");
    allWindowsButton_->setStyleSheet("background-color: #e0e0e0; color: black; border: none; padding: 5px 10px; border-radius: 5px;");
    activeFilter_ = true;
}

void timetrackerapps::setAllWindowFilter()
{
    activeWindowsButton_->setStyleSheet("background-color: #e0e0e0; color: black; border: none; padding: 5px 10px; border-radius: 5px;");
    allWindowsButton_->setStyleSheet("background-color: #559ad0; color: white; border: none; padding: 5px 10px; border-radius: 5px;");
    activeFilter_ = false;
}


void timetrackerapps::addWindowItem(QString appName, QString time) {
    QListWidgetItem* item = new QListWidgetItem();

    QWidget* customWidget = new QWidget();
    QHBoxLayout* widgetLayout = new QHBoxLayout(customWidget);
    widgetLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* appNameLabel = new QLabel(appName);
    appNameLabel->setStyleSheet("color: white;");
    QLabel* timeLabel = new QLabel(time);
    timeLabel->setStyleSheet("color: white;");
    widgetLayout->addWidget(appNameLabel);
    widgetLayout->addStretch();
    widgetLayout->addWidget(timeLabel);
    customWidget->setLayout(widgetLayout);


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

        // Ищем QLabel внутри layout
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

        // Предполагаем, что имя приложения находится в первом QLabel
        QLabel* appNameLabel = qobject_cast<QLabel*>(layout->itemAt(0)->widget());
        if (appNameLabel && appNameLabel->text() == appName)
            return true;
    }
    return false;
}
