#include "Star.h"
#include "WorldManager.h"

Star::Star(df::Vector pos, float s)
{
	setType("star");
	setSprite("starsprite");
	setPosition(pos);
	setSolidness(df::SOFT);
	setAltitude(3);
	setVelocity(df::Vector(s, 0));
}

int Star::eventHandler(const df::Event* p_e) {
	if (getPosition().getX() < -5 && getVelocity().getX() < 0) WM.markForDelete(this);
	if (getPosition().getX() > DM.getHorizontal() + 8 && getVelocity().getX() > 0) WM.markForDelete(this);
	return 0;
}
