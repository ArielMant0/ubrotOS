#include "device/clock.h"
#include "machine/cgascr.h"
#include "machine/plugbox.h"
#include "machine/pic.h"

Clock g_clock;

Clock::Clock() : m_hours(0), m_minutes(0), m_seconds(0) {
	g_plugbox.assign(g_plugbox.timer, *this);
	g_pic.allow(timer);
}

void Clock::printTime() {
	int x = 72;
	int y = 0;

	g_cga.show(x,y, char((m_hours/10)+'0'));
	g_cga.show(x+1,y, char((m_hours%10)+'0'));
	g_cga.show(x+2,y, ':');
	g_cga.show(x+3,y, char((m_minutes/10)+'0'));
	g_cga.show(x+4,y, char((m_minutes%10)+'0'));
	g_cga.show(x+5,y, ':');
	g_cga.show(x+6,y, char((m_seconds/10)+'0'));
	g_cga.show(x+7,y, char((m_seconds%10)+'0'));
}

void Clock::trigger() {
	printTime();
	addSecond();
}

void Clock::addSecond() {
	if (m_seconds == 59) {
		m_seconds = 0;
		addMinute();
	} else {
		m_seconds++;
	}
}

void Clock::addMinute() {
	if (m_minutes == 59) {
		m_minutes = 0;
		addHour();
	} else {
		m_minutes++;
	}
}

void Clock::addHour() {
	if (m_hours == 23) {
		m_hours == 0;
	} else {
		m_hours++;
	}
}
