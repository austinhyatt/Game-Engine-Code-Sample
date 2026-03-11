#include "Object.h"
#include "Vector.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Animation.h"

df::Object::Object() {
	//assign default ID
	static int objectIdCount = 0;
	id = objectIdCount;
	objectIdCount++;

	type = "object";
	position = Vector();
	direction = Vector();
	speed = 0;
	altitude = MAX_ALTITUDE / 2;
	solidness = df::Solidness::HARD;
	animation;
	box = Box(position, 1, 1);

	//Add self to game world
	WM.insertObject(this);
}

df::Object::~Object() {
	WM.removeObject(this);
}

void df::Object::setId(int new_id) { id = new_id; }

int df::Object::getId() const { return id; }

void df::Object::setType(std::string new_type) { type = new_type; }

std::string df::Object::getType() const { return type; }

void df::Object::setPosition(Vector new_position) { position = new_position; }

df::Vector df::Object::getPosition() const { return position; }

int df::Object::eventHandler(const df::Event* p_event) { return 0; }

void df::Object::setSpeed(float new_speed) { speed = new_speed; }

float df::Object::getSpeed() const { return speed; }

void df::Object::setDirection(Vector new_direction) { direction = new_direction; }

df::Vector df::Object::getDirection() const { return direction; }

void df::Object::setVelocity(Vector new_velocity) {
	speed = new_velocity.getMagnitude();
	new_velocity.normalize();
	direction = new_velocity;
}

df::Vector df::Object::getVelocity() const {
	Vector out = Vector(direction.getX(), direction.getY());
	out.scale(speed);
	return out;
}

int df::Object::getAltitude() const { return altitude; }

int df::Object::setAltitude(int new_altitude) {
	if (new_altitude <= MAX_ALTITUDE) {
		altitude = new_altitude;
		return 0;
	}
	return -1;
}

df::Vector df::Object::predictPosition() { return position + getVelocity(); }

bool df::Object::isSolid() const {return solidness!=SPECTRAL;}

void df::Object::setSolidness(Solidness new_solid) {solidness = new_solid;}

df::Solidness df::Object::getSolidness() const {return solidness;}

int df::Object::setSprite(std::string sprite_label) { 
	Sprite* temp_sprite = RM.getSprite(sprite_label);
	if (temp_sprite == NULL)
		return -1;
	animation.setSprite(temp_sprite);
	setBox(animation.getBox());
	return 0;
}

void df::Object::setAnimation(Animation new_animation) { animation = new_animation; }

df::Animation df::Object::getAnimation() const {return animation;}

int df::Object::draw() { return animation.draw(position); }

void df::Object::setBox(Box new_box) {box = new_box;}

df::Box df::Object::getBox() const { return box; }


