#include "Timer.hpp"
#include <string>
#include <iostream>
#include <QDebug>

std::string Timer::currentTime()
{
	return std::to_string(time.hours) + " h. " + std::to_string(time.minutes) + " min";
}

void Timer::tick()
{
	qInfo() << "Full time: " << currentTime();
	qInfo() << "Seconds (before): " << time.seconds;
	plusSecond();
	qInfo() << "Seconds (after): " << time.seconds;
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
	qInfo() << "PlusSecond";
	if (time.seconds == 59)
	{
		time.seconds = 0;
		plusMinute();
	}
	else
	{
		qInfo() << "seconds++";
		time.seconds++;
	}
}

