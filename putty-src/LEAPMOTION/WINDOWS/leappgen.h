#ifndef LEAP_GEN_H
#define LEAP_GEN_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif
#define WM_LEAP_MOVED	(WM_APP + 1000)

	typedef struct _LeapPosition {
		int reduced;
		float x;
		float y;
		float z;
		float _x;
		float _y;
		float _z;
		int ix;
		int iy;
		int iz;
	} LeapPosition;

	typedef struct _LeapFingers {
		int count;
		LeapPosition data[10];
	} LeapFingers;

	void initializeLeap(__in HWND hwnd);
	int getFingers(__inout LeapFingers *fingers);
	void startLeap();
	void stopLeap();
	void releaseLeap();
#ifdef __cplusplus
}
#endif

#endif