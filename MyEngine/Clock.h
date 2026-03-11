#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <Windows.h>

namespace df {

	class Clock {

	private:
		long int previous_time; // XXXPrevious call to delta() (in microseconds).
		static long int getConvertedSystemTime(); //Helper function converting SYSTEMTIME to miliseconds

	public:
		// Sets previous_time to current time.
		Clock();

		// Return time elapsed since delta() was called, -1 if error.
		// Resets clock time.
		// Units are microseconds.
		long int delta();

		// Return time elapsed since delta() was called, -1 if error.
		// Does not reset clock time.
		// Units are microseconds.
		long int split() const;
	};

}
#endif
