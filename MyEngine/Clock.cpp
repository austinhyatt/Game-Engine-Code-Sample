#include <Windows.h>
#include <cstdio>

#include "Clock.h"
df::Clock::Clock() {
	previous_time = getConvertedSystemTime();
}

long int df::Clock::split() const {
	return getConvertedSystemTime() - previous_time;
}

long int df::Clock::delta() {
	long int out = split();
	previous_time = getConvertedSystemTime();
	return out;
}

long int df::Clock::getConvertedSystemTime(){
	SYSTEMTIME st;
	GetSystemTime(&st);
	return (st.wDay * 24 * 60 * 60 * 1000000)
		+ (st.wHour * 60 * 60 * 1000000)
		+ (st.wMinute * 60 * 1000000)
		+ (st.wSecond * 1000000)
		+ (st.wMilliseconds * 1000);
}

