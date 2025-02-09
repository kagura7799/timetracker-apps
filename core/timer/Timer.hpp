#ifndef TIMER_HPP
#define TIMER_HPP

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

private:
    int totalSeconds;
    bool running;
    std::chrono::steady_clock::time_point lastStartTime;
};

#endif // TIMER_HPP
