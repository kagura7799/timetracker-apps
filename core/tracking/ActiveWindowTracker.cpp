#include "ActiveWindowTracker.hpp"
#include <iostream>
#include <QDebug>

ActiveWindowTracker::ActiveWindowTracker()
{
}

std::wstring ActiveWindowTracker::getActiveWindowName()
{
    HWND hWin = GetForegroundWindow();
    if (!hWin)
        return L"";

    wchar_t windowTitle[256];
    int length = GetWindowTextW(hWin, windowTitle, 256);

    if (length <= 0) 
    {
        return L"";
    }

    std::wstring fullTitle(windowTitle, length);

    // symbol followed by the title
    size_t pos = fullTitle.rfind(L" - ");
    
    // cut off the line leaving the title
    if (pos != std::wstring::npos)
    {
        return fullTitle.substr(pos + 3);
    }

    return fullTitle;
}

void ActiveWindowTracker::switchActiveWindowForTimer()
{

}
