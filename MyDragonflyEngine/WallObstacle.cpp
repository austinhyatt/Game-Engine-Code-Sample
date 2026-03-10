#include "WallObstacle.h"
#include "EventOut.h"
#include "WorldManager.h"

WallObstacle::WallObstacle(df::Vector pos, float s)
{
	setType("wallobstacle");
	setSprite("wallsprite");
	setPosition(pos);
	setVelocity(df::Vector(s, 0));
	setSolidness(df::SOFT);
	setAltitude(3);
}

int WallObstacle::eventHandler(const df::Event* event)
{
	if (event->getType() == df::OUT_EVENT) {
		WM.markForDelete(this);
	}
	return 0;
}
