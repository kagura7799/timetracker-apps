#pragma once

#include "core/timer/Timer.hpp"
#include "gui/timetrackerapps.h"
#include <QString>

class TotalTime
{
public:
	void TotalTimeTicker(timetrackerapps* window);

private:
	Timer timer;
};

