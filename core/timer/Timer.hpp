#pragma once

#include <string>
#include <iostream>

struct Time
{
	int hours;
	int minutes;
	int seconds;
};

class Timer 
{
public:
	Timer() : time{ 0, 0, 0 } {}

	std::string currentTime();
	void tick();

private:
	Time time;

	void plusHour();
	void plusMinute();
	void plusSecond();
};