#include "ActiveWindowTracker.hpp"
#include "gui/timetrackerapps.h"
#include <iostream>
#include <QDebug>
#include <QString>

ActiveWindowTracker::ActiveWindowTracker() : previousWindowTitle("")
{

}

std::string ActiveWindowTracker::getProcessPath()
{
    HWND hWin = GetForegroundWindow();
    if (!hWin)
        return "";

    DWORD pid;
    GetWindowThreadProcessId(hWin, &pid);

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProcess) return "unknown";

    char filename[MAX_PATH] = { 0 };
    DWORD size = MAX_PATH;

    if (!QueryFullProcessImageNameA(hProcess, 0, filename, &size))
    {
        return "unknown";
    }

    CloseHandle(hProcess);

    return std::string(filename);
}

std::string ActiveWindowTracker::getFullActiveAppName()
{
    std::string filePath = getProcessPath();

    DWORD dummy;
    DWORD size = GetFileVersionInfoSizeA(filePath.c_str(), &dummy);
    if (size == 0) return "unknown";

    std::vector<BYTE> buffer(size);
    if (!GetFileVersionInfoA(filePath.c_str(), 0, size, buffer.data())) return "";

    VS_FIXEDFILEINFO* fileInfo;
    UINT len;
    if (!VerQueryValueA(buffer.data(), "\\", (LPVOID*)&fileInfo, &len)) return "";

    char* productName = nullptr;
    if (VerQueryValueA(buffer.data(), "\\StringFileInfo\\040904b0\\FileDescription", (LPVOID*)&productName, &len)) 
    {
        return std::string(productName);
    }

    return "unknown";
}

std::string ActiveWindowTracker::handleTitleString(std::string str)
{
    size_t pos = str.find(".exe");
    if (pos != std::string::npos)
    {
        str.erase(pos, 4);
    }

    size_t lastSlash = str.find_last_of("\\/");
    if (lastSlash == std::string::npos) return str;

    return str.substr(lastSlash + 1);
}

void ActiveWindowTracker::trackActiveWindowTime(timetrackerapps* window)
{
    timer.tick();

    std::string currentWindowTitle = getFullActiveAppName();

    // if app version was not found, go to get process name
    if (currentWindowTitle == "unknown")
        currentWindowTitle = handleTitleString(getProcessPath());

    std::wstring wCurrentWindowTitle(currentWindowTitle.begin(), currentWindowTitle.end());
    std::string time = timer.currentTime();

    if (currentWindowTitle != previousWindowTitle)
    {
        qInfo() << "Active window changed: " << QString::fromStdString(currentWindowTitle);
        addItem(time, wCurrentWindowTitle, window);
        previousWindowTitle = currentWindowTitle;
    }
}

void ActiveWindowTracker::addItem(std::string time, std::wstring title, timetrackerapps* window)
{
    window->addWindowItem(QString::fromStdWString(title), QString::fromStdString(time));
}

#pragma comment(lib, "version.lib")