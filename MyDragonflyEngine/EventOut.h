#ifndef EVENT_OUT_H
#define EVENT_OUT_H

#include "Event.h"

namespace df {

	const std::string OUT_EVENT = "df::out";

	class EventOut : public Event {

	public:
		EventOut();
	};

}
#endif

