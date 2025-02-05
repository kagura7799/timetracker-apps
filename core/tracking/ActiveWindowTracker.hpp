#include <Windows.h>
#include <psapi.h>
#include <string>
#include "gui/timetrackerapps.h"
#include "core/timer/Timer.hpp"
#include "app/AppManager.hpp"

class ActiveWindowTracker
{
public:
	ActiveWindowTracker(AppManager& appManager);
	void updateListApps(timetrackerapps* window);
	std::string getProcessPath();
	std::string getFullActiveAppName();

private:
	void addItem(std::string time, std::wstring title, timetrackerapps* window);
	std::string previousWindowTitle;
	std::string handleTitleString(std::string str);
	AppManager& appManager_;
};
