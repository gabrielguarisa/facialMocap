#include "Windows.h"

std::string textHelp[5] = { "H - Exibe/Esconde Ajuda", "1 - Calibrar", "2 - Rastrear", "3 - Parar", "Esc - Sair" };
std::string textWarning[2] = { "Tracking not done!", "Wait and try again!" };

//---------------------------------------------------------------------
//	function to callback
//---------------------------------------------------------------------
void CallBackFunc(int event, int x, int y, int flags, void* this_pointer)
{
	Inputs *inputs = (Inputs*)this_pointer;
	inputs->mouseCallback(event, x, y, flags, 0);
}

//---------------------------------------------------------------------
//	constructor
//---------------------------------------------------------------------
Windows::Windows()
{
	cap.updateFrame(&frame);

	inputs = new Inputs(frame.cols, frame.rows);

	//	default settings
	t_info.vmin = 10;
	t_info.vmax = 256;
	t_info.smin = 30;
	//
	t_info.smax = 256;
	t_info.hmin = 0;
	t_info.hmax = 180;
	//

	//	creating windows
	cv::namedWindow(windowName_Trackbar, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(windowName_Original, CV_WINDOW_AUTOSIZE);

	//	mouse callback
	cv::setMouseCallback(windowName_Original, CallBackFunc, inputs);

	//	creating the trackbars
	cv::createTrackbar("Vmin", windowName_Trackbar, &t_info.vmin, 256, 0);
	cv::createTrackbar("Vmax", windowName_Trackbar, &t_info.vmax, 256, 0);
	cv::createTrackbar("Smin", windowName_Trackbar, &t_info.smin, 256, 0);
	//
	cv::createTrackbar("Smax", windowName_Trackbar, &t_info.smax, 256, 0);
	cv::createTrackbar("Hmin", windowName_Trackbar, &t_info.hmin, 256, 0);
	cv::createTrackbar("Hmax", windowName_Trackbar, &t_info.hmax, 256, 0);
	//
}

//---------------------------------------------------------------------
//	destructor
//---------------------------------------------------------------------
Windows::~Windows()
{
	cv::destroyAllWindows();
	cap.~Capture();
}

//---------------------------------------------------------------------
//	main method
//---------------------------------------------------------------------
void Windows::mainLoop()
{
	while (C_S_CAPTURE != END)
	{
		cap.updateFrame(&frame);

		if (C_S_CAPTURE == PRE_TRACK)
		{
			output = new Output();
			output->setFileName("output");
			C_S_CAPTURE = TRACK;
			clock.clearTime();
		}

		if (C_S_CAPTURE == TRACK)
			clock.startClock();
		
		tracking.updateFrames(frame, t_info);

		if (C_S_SELECTION == SELECTED_UNMARKED)
			tracking.setMarker(inputs->mouseSelection);

		if (C_S_CAPTURE != INIT)
		{
			imshow(windowName_Original, tracking.camshift());
		}else
		{
			if (HELP)
			{
				cv::Point2d point(0, 50);
				for (int i = 0; i < 5; i++, point.y+=50)
					cv::putText(frame, textHelp[i], point, cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(0, 0, 0, 0));
			}
			else if (WARNING_TYPE == TND)
			{
				cv::Point2d point(0, 130);
				cv::putText(frame, textHelp[0], point, cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(0, 0, 0, 0));
			}
			else if (WARNING_TYPE == WTA)
			{
				cv::Point2d point(0, 130);
				cv::putText(frame, textHelp[1], point, cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(0, 0, 0, 0));
			}


			imshow(windowName_Original, frame);
		}
			

		inputs->keyboard();

		if (C_S_CAPTURE == TRACK)
		{
			currentFrame++;
			clock.endClock();
			output->addMotion();
		}

		if (C_S_CAPTURE == STOP)
		{
			output->exportToBvh(clock.getFrameTime());
			output->closeBVHFile();
			output->~Output();
			clock.clearTime();
			C_S_CAPTURE = CALIBRATION;
		}
	}
}