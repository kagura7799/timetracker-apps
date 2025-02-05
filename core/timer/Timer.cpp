#include "Timer.hpp"
#include <string>
#include <iostream>
#include <QDebug>

std::string Timer::currentTime()
{
	return std::to_string(time.hours) + " h. " + std::to_string(time.minutes) + " min. " + std::to_string(time.seconds) + " sec";
}

void Timer::tick()
{
	plusSecond();
}

void Timer::plusHour()
{
	if (time.hours == 24)
	{
		time.hours = 0;
		time.minutes = 0;
		time.seconds = 0;
	}

	time.hours++;
}

void Timer::plusMinute()
{
	if (time.minutes == 59)
	{
		time.minutes = 0;
		plusHour();
	}
	else 
	{
		time.minutes++;
	}
}

void Timer::plusSecond()
{
	if (time.seconds == 59)
	{
		time.seconds = 0;
		plusMinute();
	}
	else
	{
		time.seconds++;
	}
}

