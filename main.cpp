#include "Windows.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

STATUS_SELECTION C_S_SELECTION = NO_SELECTION;
STATUS_CAPTURE C_S_CAPTURE = INIT;
WARNING WARNING_TYPE = NONE;
Marker marker[MAX_MARKERS];
int currentFrame = 0;

int main(int argc, const char** argv)
{
	Windows windows;

	windows.mainLoop();

	windows.~Windows();

	return 0;
}
