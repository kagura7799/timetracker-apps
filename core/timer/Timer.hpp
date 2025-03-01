#pragma once

#include <chrono>
#include <string>
#include <QDebug>

class Timer {
public:
    Timer();

    void start();
    void stop();

    int getTimeInSeconds() const;
    std::string getTimeFormatted(int time) const;

    int getElapsedSeconds() const;
    void setElapsedSeconds(int seconds);

private:
    int elapsedSeconds;
    int totalSeconds;
    bool running;
    std::chrono::steady_clock::time_point lastStartTime;

    void resetElapsedSeconds();
};
