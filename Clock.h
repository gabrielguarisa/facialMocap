#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <ctime>
#include "Global.h"

class Clock{
private:

	clock_t startTime,
			endTime;

	double total;
public:

	Clock();

	void startClock();

	void endClock();

	double timeInSeconds();

	double getFrameTime();

	void clearTime();
};

#endif //_CLOCK_H_