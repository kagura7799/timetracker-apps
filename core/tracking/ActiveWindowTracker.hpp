#include <Windows.h>
#include <psapi.h>
#include <string>
#include "gui/timetrackerapps.h"
#include "core/timer/Timer.hpp"

class ActiveWindowTracker
{
public:
	ActiveWindowTracker();
	void trackActiveWindowTime(timetrackerapps* window);
	std::string getProcessPath();
	std::string getFullActiveAppName();

private:
	void addItem(std::string time, std::wstring title, timetrackerapps* window);
	Timer timer;
	std::string previousWindowTitle;
	std::string handleTitleString(std::string str);
};
