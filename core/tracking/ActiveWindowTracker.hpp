#include <Windows.h>
#include <psapi.h>
#include <string>
#include "gui/timetrackerapps.h"
#include "core/timer/Timer.hpp"
#include "app/AppManager.hpp"
#include "core/presenter/Presenter.hpp"

class ActiveWindowTracker
{
public:
	ActiveWindowTracker(AppManager& appManager);
	void updateListApps(timetrackerapps* window);
	std::string getProcessPath();
	std::string getFullActiveAppName();

private:
	std::string handleTitleString(std::string str);
	AppManager& appManager_;
	Timer timer;
	Presenter presenter;
	qint64 lastSwitchTime;
};