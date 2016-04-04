#ifndef _INPUTS_H_
#define _INPUTS_H_

#include <opencv2/opencv.hpp>
#include "Global.h"

class Inputs{
private:

	int frameCols,
		frameRows;
public:

	Inputs(int frameCols, int frameRows);
	
	void keyboard();
	
	void mouseCallback(int event, int x, int y, int, void*);
	
	cv::Rect mouseSelection;
};

#endif //_INPUTS_H_