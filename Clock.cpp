#include "Clock.h"

Clock::Clock()
{
	this->clearTime();
}

void Clock::startClock()
{
	startTime = clock();
}

void Clock::endClock()
{
	endTime = clock();
	total += this->timeInSeconds();
}

double Clock::timeInSeconds()
{
	clock_t clockTicksTaken = endTime - startTime;
	return clockTicksTaken / (double)CLOCKS_PER_SEC;
}

double Clock::getFrameTime()
{
	return total / currentFrame;
}

void Clock::clearTime()
{
	total = 0.0;
}