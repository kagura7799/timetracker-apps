#include "Presenter.hpp"

void Presenter::addItem(timetrackerapps* window, std::string time, std::wstring title)
{
    window->addWindowItem(QString::fromStdWString(title), QString::fromStdString(time));
}

void Presenter::updateWindowTime(timetrackerapps* window, std::string time, std::string title)
{
    window->updateWindowTime(QString::fromStdString(time),
        QString::fromStdString(time));
}

void Presenter::updateListItem(timetrackerapps* window)
{
    window->updateList();
}

void Presenter::updateTotalTimeLabel(timetrackerapps* window, QString time)
{
    window->updateTotalTimeLabel(time);
}