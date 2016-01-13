#pragma once

#include "Marker.h"

#define PointSub(a,b,c)	{c.x=a.x-b.x;c.y=a.y-b.y;}

#define MAX_MARKERS 10

#define PROPORTION 20

#define FORM 1 //0 rectangle || 1 elipse

#define SFORM 2

enum STATUS_SELECTION { NO_SELECTION, SELECTED_UNMARKED };
enum STATUS_CAPTURE { INIT, CALIBRATION, PRE_TRACK, TRACK, STOP, END };

extern Marker marker[MAX_MARKERS];
extern int currentFrame;
extern STATUS_SELECTION C_S_SELECTION;
extern STATUS_CAPTURE C_S_CAPTURE;
extern bool BLOCK;
extern bool HELP;

typedef struct
{
	int hmin,
		hmax,
		vmin,
		vmax,
		smin,
		smax;
}trackbarInfo;

template <typename T>
std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}