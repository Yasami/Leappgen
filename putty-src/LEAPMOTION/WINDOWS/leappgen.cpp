#include "leappgen.h"

#include <Leap.h>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>

#include "../../misc.h"

using namespace Leap;

class PGenListener : public Leap::Listener {
public:
	PGenListener() : 
		m_frameCounter(0), m_hwnd(0), m_frameId(0), m_started(true) {}
	
	virtual void onInit(const Leap::Controller&) { 
#ifdef _DEBUG
		std::cout << __FUNCTION__ << std::endl;
#endif
	}

	virtual void onConnect(const Leap::Controller&){  
#ifdef _DEBUG
		std::cout << __FUNCTION__ << std::endl;
#endif
	}

	virtual void onDisconnect(const Leap::Controller&){ 
#ifdef _DEBUG
		std::cout << __FUNCTION__ << std::endl;
#endif
	}

	virtual void onExit(const Leap::Controller&){ 
#ifdef _DEBUG
		std::cout << __FUNCTION__ << std::endl;
#endif
	}

	virtual void onFrame(const Leap::Controller& controller){
		std::lock_guard<std::mutex> lock(m_mutex);
		if (!m_started)
			return;

		if (m_frameId)
			return;

		const Leap::Frame frame = controller.frame();
		auto  screen = controller.locatedScreens()[0];
		const Leap::FingerList fingers = frame.fingers();
		LeapFingers lf;
		lf.count = fingers.count();
		if (lf.count == 0)
		    return;

		int fingerCount = min(lf.count, 10);
		for (int i = 0; i < fingerCount; ++i) {
			Leap::Finger finger = fingers[i];
			Leap::Vector position = finger.tipPosition();
			Leap::Vector projected = screen.project(position, true, 1.0);
			byte x = static_cast<int>(position.x * 10) & 0xFF;
			byte y = static_cast<int>(position.y * 10) & 0xFF;
			byte z = static_cast<int>(position.z * 10) & 0xFF;
			int reduced = x & 0xFF;
			reduced |= (y & 0xFF) << 8;
			reduced |= (z & 0xFF) << 16;
			reduced |= (finger.id() & 0xFF) << 24;
			lf.data[i].reduced = reduced;
			lf.data[i].x = projected.x;
			lf.data[i].y = projected.y;
			lf.data[i].z = projected.z;
			lf.data[i]._x = position.x;
			lf.data[i]._y = position.y;
			lf.data[i]._z = position.z;
			lf.data[i].ix = x;
			lf.data[i].iy = y;
			lf.data[i].iz = z;
		}
		m_fingers = lf;
		m_frameId = frame.id();
		PostMessage(m_hwnd, WM_LEAP_MOVED, 0, 0);
	}

	virtual void onFocusGained(const Leap::Controller&){
#ifdef _DEBUG
		std::cout << __FUNCTION__ << std::endl;
#endif
	}

	virtual void onFocusLost(const Leap::Controller&){
#ifdef _DEBUG
		std::cout << __FUNCTION__ << std::endl;
#endif
	}

	void setWindow(HWND hwnd) {
		m_hwnd = hwnd;
	}
	
	void getFingers(LeapFingers *fingers) {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_frameId == 0)
			return;
		
		*fingers = m_fingers;
		m_frameId = 0;
	}

	void  start() {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_frameId = 0;
		m_started = true;
	}

	void stop() {
		m_started = false;
	}

	static Leap::Controller& getController() 
	{
		static Leap::Controller s_controller;
		return  s_controller;
	}

	static PGenListener& getLitener()
	{
		static PGenListener s_listener;
		return s_listener;
	}
private:
	int m_frameCounter;
	HWND m_hwnd;
	volatile int64_t m_frameId;
	volatile bool m_started;
	LeapFingers m_fingers;
	std::mutex m_mutex;
};

void initializeLeap(HWND hwnd) {
	PGenListener& listener  = PGenListener::getLitener();
	listener.setWindow(hwnd);

#ifdef _DEBUG
	AllocConsole();
	FILE *fp;
	freopen ( "CONOUT$", "w", stdout ); 
#endif
}

int getFingers(__inout LeapFingers *fingers){

	PGenListener& listener  = PGenListener::getLitener();
	listener.getFingers(fingers);
	return fingers->count;
}

void startLeap() {
	PGenListener& listener  = PGenListener::getLitener();
	Leap::Controller& controller = PGenListener::getController();
	controller.addListener(listener);
	std::cout << controller.isConnected() << std::endl;
	listener.start();
}

void stopLeap() {
	Leap::Controller& controller = PGenListener::getController();
	PGenListener& listener  = PGenListener::getLitener();
	listener.stop();
	controller.removeListener(listener);
}

void releaseLeap() {
#ifdef _DEBUG
	FreeConsole();
#endif
}
