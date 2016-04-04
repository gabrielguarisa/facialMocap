#include "Inputs.h"

#define RECT_W 2
#define RECT_H 2
bool BLOCK = false;
bool HELP = false;

Inputs::Inputs(int frameCols, int frameRows) : frameCols(frameCols), frameRows(frameRows) {}

void Inputs::mouseCallback(int event, int x, int y, int, void*)
{
	if (C_S_CAPTURE == CALIBRATION)
	{
		switch (event)
		{
		case CV_EVENT_LBUTTONDOWN:
			mouseSelection.x = x - RECT_W / 2;
			mouseSelection.y = y - RECT_H / 2;
			mouseSelection.width = RECT_W;
			mouseSelection.height = RECT_H;
			mouseSelection &= cv::Rect(0, 0, frameCols, frameRows);
			break;
		case CV_EVENT_LBUTTONUP:
			if (mouseSelection.width > 0 && mouseSelection.height > 0)
				C_S_SELECTION = SELECTED_UNMARKED;
			break;
		case CV_EVENT_RBUTTONDOWN:
			for (int i = 0; i < MAX_MARKERS; i++)
			{
				if (marker[i].isSelected && marker[i].rect.contains(cv::Point(x, y)))
					marker[i].isSelected = false;
			}
			break;
		}
	}
}

void Inputs::keyboard()
{
	switch (cv::waitKey(20))
	{
	case '3':
		if (C_S_CAPTURE != TRACK) 
			WARNING_TYPE = TND;
		else
		{
			C_S_CAPTURE = STOP;
			BLOCK = true;
		}
		break;
	case '2':
		if (C_S_CAPTURE == CALIBRATION)
			C_S_CAPTURE = PRE_TRACK;

		break;
	case '1':
		if (C_S_CAPTURE == INIT || C_S_CAPTURE == STOP) 
			C_S_CAPTURE = CALIBRATION;
		break;
	case 'h': case 'H':
		HELP = !HELP;
		break;
	case '#':
		HELP = !HELP;
		break;
	case 27:
		if (C_S_CAPTURE == TRACK)
			WARNING_TYPE = TND;
		else if (BLOCK)
			WARNING_TYPE = WTA;
		else
			C_S_CAPTURE = END;
		break;
	}
}