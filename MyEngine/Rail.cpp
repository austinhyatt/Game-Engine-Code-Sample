#include "Rail.h"
#include "Animation.h"
#include "ResourceManager.h";
#include "ColorObstacle.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "WallObstacle.h"
#include "Star.h"
#include "WorldManager.h"
#include "ObjectList.h"

Rail::Rail(df::Vector v, int dir, int diff) {
	setType("rail");
	setSprite("railsprite");
	setAltitude(1);
	setSolidness(df::SPECTRAL);
	setPosition(v);

	lastColor = df::Color::RED;
	direction = dir;
	spawnTimer = 0;
	difficulty = diff;
	speed = (.3 + (diff * .13)) * 1.38;

	//spawnObstacle(10, .5, df::Color::CYAN);
}

int Rail::eventHandler(const df::Event* event)
{
	speed += ((difficulty/1.2) * .0005);
	if (event->getType() == df::STEP_EVENT) {
		//const df::EventStep* k = dynamic_cast <const df::EventStep*> (event);
		if (spawnTimer < 0)
			spawnObstacle(rand() % 32 + 12, speed, getRandomColor(lastColor));
		else
			spawnTimer--;
	}
	return 0;
}

void Rail::spawnObstacle(int l, float s, df::Color color)
{
	df::Vector spawn = df::Vector((direction > 0 ? 0 : df::WINDOW_HORIZONTAL_CHARS_DEFAULT+4) - (l/2 * direction), getPosition().getY());
	ColorObstacle* c = new ColorObstacle(spawn, l, s, color);
	int r = rand() % 11;
	df::Vector wallSpawn = df::Vector(spawn.getX() + (r > 3 ? l + 2 : l *-1 -2) / 2, spawn.getY());
	if (r < 8)
		WallObstacle* w = new WallObstacle(wallSpawn, s*direction);
	int sr = rand() % 20;
	if (sr>16 && WM.getAllObjectsOfType("star").getCount() == 0) {
		Star* star = new Star(spawn, s);
		star->setDirection(df::Vector(direction, 0));
	}
	c->setDirection(df::Vector(direction, 0));
	
	spawnTimer = 82 + (l*.75) + (difficulty*9) - (int)(speed*50);
}

df::Color Rail::getRandomColor(df::Color bannedColor, bool scramble)
{
	df::Color c = lastColor;

	while (c == lastColor || ((rand()<rand() && c==secondLastColor) || (scramble && c == bannedColor))) {
		switch (rand() % 3)
		{
		case 0:
			c = df::Color::CYAN;
			break;
		case 1:
			c = df::Color::YELLOW;
			break;
		case 2:
			c = df::Color::RED;
			break;
		}
	}
	if (otherRail1->lastColor == c && otherRail2->lastColor == c) {
		if (rand() > rand())
			otherRail1->getRandomColor(c, true);
		else
			otherRail2->getRandomColor(c, true);
		getRandomColor(c);
	}
	secondLastColor = lastColor;
	lastColor = c;
	return c;
}

void Rail::setOtherRails(Rail* r1, Rail* r2)
{
	otherRail1 = r1;
	otherRail2 = r2;
}
