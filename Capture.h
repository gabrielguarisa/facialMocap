/*********************
******* Capture ******
*********************/
#ifndef _CAPTURE_H_
#define _CAPTURE_H_

#include <opencv2/opencv.hpp>

#define CAM 0

class Capture{
private:
	cv::VideoCapture cap;
public:
	Capture();

	~Capture();

	void updateFrame(cv::Mat *frame);
};

#endif