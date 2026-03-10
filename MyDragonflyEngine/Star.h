#ifndef _STAR_
#define _STAR_

#include "Object.h"
#include "EventOut.h"

class Star : public df::Object {
public:
	Star(df::Vector pos, float s);

	int eventHandler(const df::Event* p_e) override;
};
#endif