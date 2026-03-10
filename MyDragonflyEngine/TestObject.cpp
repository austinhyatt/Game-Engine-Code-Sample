#include "Event.h"
#include "Object.h"
#include "TestObject.h"
#include "EventStep.h"	
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventView.h"

df::TestObject::TestObject() {
	setType("testobject");
	step = 0;
	outOfBounds = false;
	collided = false;
}

int df::TestObject::eventHandler(const Event* event) {
	if (getType() == "star")
		return 0;

	if (event->getType() == df::STEP_EVENT)	{
		const df::EventStep* e = dynamic_cast <const df::EventStep*> (event);
		step = e->getStepCount();
		//printf("obj recieved value from event:\t%i\n", step);
		return 1;
	}
	if (getType() == "wasd") {
		if (event->getType() == df::KBD_EVENT) {
			const df::EventKeyboard* k = dynamic_cast <const df::EventKeyboard*> (event);
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::W)
				setVelocity(Vector(0, -.15));
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::S)
				setVelocity(Vector(0, .15));
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::A)
				setVelocity(Vector(-.15, 0));
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::D)
				setVelocity(Vector(.15, 0));
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::COMMA)
				getAnimation().getSprite()->setSlowdown(10);
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::SPACE) {
				WM.setBoundary(Box(Vector(), 160, 48));
				WM.setViewFollowing(this);
			}
			return 2;
		}
	}
	if (getType() == "arrowkeys") {
		if (event->getType() == df::KBD_EVENT) {
			const df::EventKeyboard* k = dynamic_cast <const df::EventKeyboard*> (event);
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::UPARROW)
				setVelocity(Vector(0, -.15));
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::DOWNARROW)
				setVelocity(Vector(0, .15));
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::LEFTARROW)
				setVelocity(Vector(-.15, 0));
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::RIGHTARROW)
				setVelocity(Vector(.15, 0));
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::COMMA) 
				getAnimation().getSprite()->setSlowdown(10);
			if (k->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && k->getKey() == df::Keyboard::PERIOD)
				getAnimation().getSprite()->setSlowdown(.5);
			return 2;
		}
	}
	if (event->getType() == df::MSE_EVENT) {
		const df::EventMouse* m = dynamic_cast <const df::EventMouse*> (event);
		if (m->getMouseAction() == EventMouseAction::CLICKED && m->getMouseButton() == df::Mouse::RIGHT) {
			df::Object* ch = new df::TestObject();
			ch->setPosition(getPosition());
			ch->setAltitude(MAX_ALTITUDE);
			ch->setSolidness(SPECTRAL);
			ch->setType("star");
			RM.getSound("fire")->play();
			df::EventView ev = df::EventView("starcounter", 1, true);
			WM.onEvent(&ev);
		}
	}
	if (event->getType() == df::OUT_EVENT) {
		if (!outOfBounds) {
			printf("Obj %i gone out of bounds\n", getId());
			outOfBounds = true;
		}
		return 4;
	}
	if (event->getType() == df::COLLISION_EVENT) {
		if (!collided) {
			const df::EventCollision* c = dynamic_cast <const df::EventCollision*> (event);
			printf("Obj %i collided with obj %i\n", getId(), c->getObject2()->getId());
			collided = true;
		}
		return 5;
	}
	return 0;
}

int df::TestObject::draw() {
	if (getType() == "star")
		return DM.drawCh(getPosition(), '*', WHITE);
	return Object::draw();
}