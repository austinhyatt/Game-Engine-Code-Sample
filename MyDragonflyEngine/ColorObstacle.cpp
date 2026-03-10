#include "ColorObstacle.h"
#include "DisplayManager.h"
#include "Box.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "WorldManager.h"

ColorObstacle::ColorObstacle(df::Vector pos, int l, float s, df::Color c)
{
	setType("colorobstacle");
	setPosition(pos);
	setVelocity(df::Vector(s, 0));
	setSolidness(df::SOFT);
	setAltitude(2);
	getAnimation().getSprite()->setColor(c);
	length = l;
	color = c;

	for (int i = 0; i < length; i++)
		str += ("#");
	df::Box b = df::Box(df::Vector(-1 * length / 2, -1 * 3 / 2),
		length, 3);
	setBox(b);
}

int ColorObstacle::eventHandler(const df::Event* event)
{
	if (getPosition().getX() + length / 2 < -5 || getPosition().getX() - length / 2 > DM.getHorizontal() + 9) {
		WM.markForDelete(this);
	}
	return 0;
}

int ColorObstacle::draw()
{
	DM.drawString(getPosition(), str, df::CENTER_JUSTIFIED, color);
	DM.drawString(df::Vector(getPosition().getX(), getPosition().getY()-1), str, df::CENTER_JUSTIFIED, color);
	DM.drawString(df::Vector(getPosition().getX(), getPosition().getY()+1), str, df::CENTER_JUSTIFIED, color);

	return 0;
}
