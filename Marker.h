#ifndef _MARKER_H_
#define _MARKER_H_

#include <opencv/cv.hpp>

class Marker{
public:

	Marker(cv::Rect rect);

	Marker();
	
	std::string name(int num);

	std::string toString();

	double	x,
			y;

	bool isSelected;
	
	cv::Rect rect;
};

#endif //_MARKER_H_