#include "TotalTime.hpp"

void TotalTime::TotalTimeTicker(timetrackerapps* window)
{
	timer.tick();

	std::string currentTime = timer.currentTime();
	window->updateTotalTimeLabel(QString::fromStdString(currentTime));
}
