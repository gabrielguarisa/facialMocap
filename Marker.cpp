#include "Marker.h"
#include "Inputs.h"
Marker::Marker(cv::Rect rect) : rect(rect), isSelected(false), x(0.0), y(0.0) {}

Marker::Marker() : isSelected(false), x(0.0), y(0.0) {}

std::string Marker::name(int num)
{
	if (num == 0)
		return "nose";
	else
		return "bone"+ NumberToString(num);
}


std::string Marker::toString()
{
	return (" " + NumberToString(this->x) + " " + NumberToString(this->y) + " 0");
}