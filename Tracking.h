#ifndef _TRACKING_H_
#define _TRACKING_H_

#include <opencv2/opencv.hpp>
#include "Global.h"

class Tracking{
private:

	cv::Mat frame, hsv, hue, mask, hist, backproj;

	int vmin, vmax, smin;
public:

	void updateFrames(cv::Mat actualFrame, trackbarInfo t_info);

	void setMarker(cv::Rect mouseSelection);

	cv::Mat camshift();
};

#endif //_TRACKING_H_