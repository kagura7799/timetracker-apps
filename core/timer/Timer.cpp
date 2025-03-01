#include "Timer.hpp"

Timer::Timer() : totalSeconds(0), elapsedSeconds(0), running(false) {}

void Timer::start()
{
    if (!running)
    {
        lastStartTime = std::chrono::steady_clock::now();
        running = true;
    }
}

void Timer::stop()
{
    if (running)
    {
        totalSeconds += std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - lastStartTime).count();
        elapsedSeconds += std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - lastStartTime).count();
        running = false;
    }
}

int Timer::getTimeInSeconds() const
{
    if (running)
    {
        return totalSeconds + std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - lastStartTime).count();
    }
    return totalSeconds;
}

std::string Timer::getTimeFormatted(int time) const
{
    int h = time / 3600;
    int m = (time % 3600) / 60;
    int s = time % 60;
    return std::to_string(h) + " h. " + std::to_string(m) + " m. " + std::to_string(s) + " s.";
}

int Timer::getElapsedSeconds() const
{
    return elapsedSeconds;
}

void Timer::setElapsedSeconds(int seconds)
{
    elapsedSeconds = seconds;
    totalSeconds = seconds;
}

void Timer::resetElapsedSeconds()
{
    elapsedSeconds = 0;
}

