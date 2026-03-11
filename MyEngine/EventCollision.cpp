#include "EventCollision.h"

df::EventCollision::EventCollision() {
	setType(COLLISION_EVENT);
	pos = Vector();
	obj1 = NULL;
	obj2 = NULL;
}

df::EventCollision::EventCollision(Object* o1, Object* o2, Vector p) {
	setType(COLLISION_EVENT);
	obj1 = o1;
	obj2 = o2;
}

void df::EventCollision::setObject1(Object* new_o1) { obj1 = new_o1; }

df::Object* df::EventCollision::getObject1() const { return obj1; }

void df::EventCollision::setObject2(Object* new_o2) { obj2 = new_o2; }

df::Object* df::EventCollision::getObject2() const { return obj2; }

void df::EventCollision::setPosition(Vector new_pos) { pos = new_pos; }

df::Vector df::EventCollision::getPosition() const { return pos; }
