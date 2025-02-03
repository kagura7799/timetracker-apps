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
	std::string currentTime();
	void tick();

private:
	Time time = { 0, 0, 0 };

	void plusHour();
	void plusMinute();
	void plusSecond();
};