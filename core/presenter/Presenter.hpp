#pragma once

#include <string>
#include <QString>
#include "gui/timetrackerapps.h"
#include "app/AppManager.hpp"

class Presenter
{
public:
	void addItem(timetrackerapps* window, std::string time, std::wstring title);
	void updateWindowTime(timetrackerapps* window, std::string time, std::string title);
	void updateListItem(timetrackerapps* window);
	void updateTotalTimeLabel(timetrackerapps* window, QString time);
};

