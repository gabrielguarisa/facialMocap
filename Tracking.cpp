#include "Tracking.h"

void Tracking::updateFrames(cv::Mat actualFrame, trackbarInfo t_info)
{
	int ch[] = { 0, 0 };

	frame = actualFrame;
	vmin = t_info.vmin;
	vmax = t_info.vmax;
	smin = t_info.smin;

	cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
	inRange(hsv, cv::Scalar(MIN(t_info.hmin, t_info.hmax), MIN(t_info.smin, t_info.smax), MIN(vmin, vmax)), cv::Scalar(MAX(t_info.hmin, t_info.hmax), MAX(t_info.smin, t_info.smax), MAX(vmin, vmax)), mask);
	hue.create(hsv.size(), hsv.depth());
	mixChannels(&hsv, 1, &hue, 1, ch, 1);

	//cv::imshow("hsv", hue);
}

void Tracking::setMarker(cv::Rect mouseSelection)
{
	int hsize = 16;
	float hranges[] = { 0, 180 };
	const float* phranges = hranges;

	for (int i = 0; i < MAX_MARKERS; i++)
	{
		if (!marker[i].isSelected)
		{
			cv::Mat roi(hue, mouseSelection), maskroi(mask, mouseSelection);
			calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
			normalize(hist, hist, 0, 255, CV_MINMAX);

			marker[i].rect = mouseSelection;
			marker[i].isSelected = true;
			C_S_SELECTION = NO_SELECTION;
			break;
		}
	}
}

cv::Mat Tracking::camshift()
{
	float hranges[] = { 0, 180 };
	const float* phranges = hranges;
	for (int i = 0; i < MAX_MARKERS; i++)
	{
		if (marker[i].isSelected)
		{
			calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
			backproj &= mask;
			// get e set
			cv::RotatedRect trackBox = CamShift(backproj, marker[i].rect, cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));
			if (FORM == 0)
				rectangle(frame, marker[i].rect, cv::Scalar(0, 0, 255), SFORM, CV_AA, 0);
			else if (FORM == 1)
				ellipse(frame, trackBox, cv::Scalar(0, 0, 255), SFORM, CV_AA);
			//
			if (marker[i].rect.area() <= 1) // lost marker
				marker[i].isSelected = false;

			/*
			** CalcPos
			*/
			if (i != 0 && (C_S_CAPTURE == TRACK || C_S_CAPTURE == CALIBRATION))
			{
				//PointSub(marker[0].rect, marker[i].rect, marker[i]); //{c.x=a.x-b.x;c.y=a.y-b.y;}
				PointSub(marker[i].rect, marker[0].rect, marker[i]);
				marker[i].x /= PROPORTION;
				marker[i].y /= PROPORTION;
			}
			else if (i == 0 && C_S_CAPTURE == TRACK)
			{
				marker[0].x = marker[0].y = 0;
			}
			//
		}
	}
	return frame;
}