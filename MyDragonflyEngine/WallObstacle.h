#ifndef _WALLOBSTACLE_
#define _WALLOBSTACLE_

#include "Object.h"
#include "Color.h"
#include "Event.h"

class WallObstacle : public df::Object {
public:
	int length;

	WallObstacle(df::Vector pos, float s);

	int eventHandler(const df::Event* event) override;
};
#endif
