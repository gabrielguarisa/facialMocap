#ifndef _WINDOWS_H_
#define _WINDOWS_H_

#include <opencv2/highgui/highgui.hpp>
#include "Capture.h"
#include "Inputs.h"
#include "Tracking.h"
#include "Clock.h"
#include "Output.h"

class Windows{
private:
	const char 	*windowName_Original = "Original",
				*windowName_Trackbar = "Trackbar";

	cv::Mat frame;
	trackbarInfo t_info;
	
	Capture cap;
	Inputs *inputs;
	Output *output;
	Tracking tracking;
	Clock clock;

public:
	//---------------------------------------------------------------------
	//	constructor
	//---------------------------------------------------------------------
	Windows();

	//---------------------------------------------------------------------
	//	destructor
	//---------------------------------------------------------------------
	~Windows();

	//---------------------------------------------------------------------
	//	main method
	//---------------------------------------------------------------------
	void mainLoop();
};

#endif //_WINDOWS_H_