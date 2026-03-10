#include "Animation.h"

df::Animation::Animation()
{
	Sprite s = Sprite(0);
	setSprite(&s);
}

void df::Animation::setSprite(Sprite* new_sprite) {
	sprite = new_sprite;
	index = 0;
	slowdown_count = 0;
	name = sprite->getLabel();
}

df::Sprite* df::Animation::getSprite() const {return sprite;}

void df::Animation::setName(std::string new_name) {
	sprite->setLabel(new_name);
	name = new_name;
}

void df::Animation::setIndex(int new_index) {
	index = new_index;
	slowdown_count = 0;
}

int df::Animation::getIndex() const {return index;}

void df::Animation::setSlowdownCount(int new_slowdown_count) {slowdown_count = new_slowdown_count;}

int df::Animation::getSlowdownCount() const {return slowdown_count;}

int df::Animation::draw(Vector position)
{
	if (sprite == NULL)
		return -1;

	sprite->draw(index, position);

	if (slowdown_count == -1)
		return 0;

	slowdown_count++;
	//printf("%i\n", sprite->getSlowdown());
	if (slowdown_count >= sprite->getSlowdown()) {
		slowdown_count = 0;
		index++;
		if (index >= sprite->getFrameCount())
			index = 0;
	}
	return 0;
}

df::Box df::Animation::getBox() const
{
	if (sprite == NULL)
		return Box(Vector(-.5, -.5), 1, 1);
	return Box(Vector(-1 * sprite->getWidth() / 2, -1 * sprite->getHeight() / 2),
		sprite->getWidth(), sprite->getHeight());
}