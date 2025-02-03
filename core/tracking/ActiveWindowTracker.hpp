#include <Windows.h>
#include <psapi.h>
#include <string>

class ActiveWindowTracker
{
public:
	ActiveWindowTracker();
	void switchActiveWindowForTimer();
	std::wstring getActiveWindowName();
};