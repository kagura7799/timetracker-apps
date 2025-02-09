#pragma once

#include "core/timer/Timer.hpp"
#include "gui/timetrackerapps.h"
#include "core/presenter/Presenter.hpp"
#include <QString>

class TotalTime
{
public:
	TotalTime(AppManager& appManager);
	void TotalTimer(timetrackerapps* window);

private:
	Timer timer;
	Presenter presenter;
	AppManager& appManager_;
};

