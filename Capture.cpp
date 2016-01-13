#include "Capture.h"

Capture::Capture()
{
	cap.open(CAM);
	if (!cap.isOpened())
	{
		printf("camera not found! \n");
		getchar();
		exit(-1);
	}
}

Capture::~Capture()
{
	cap.~VideoCapture();
}

void Capture::updateFrame(cv::Mat *frame)
{
	cap >> *frame;
}


