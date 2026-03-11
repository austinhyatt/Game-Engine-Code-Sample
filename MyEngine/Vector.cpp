#include <stdio.h>
#include <cmath>

#include "Vector.h"

df::Vector::Vector() {
	x = 0;
	y = 0;
}

df::Vector::Vector(float init_x, float init_y) {
	x = init_x;
	y = init_y;
}

void df::Vector::setX(float new_x) { x = new_x; }

float df::Vector::getX() const { return x; }

void df::Vector::setY(float new_y) { y = new_y; }

float df::Vector::getY() const { return y; }

void df::Vector::setXY(float new_x, float new_y) {
	x = new_x;
	y = new_y;
}

void df::Vector::normalize() {
	float length = getMagnitude();
	if(length > 0) {
		x = x / length;
		y = y / length;
	}
}

void df::Vector::scale(float s) {
	x = x * s;
	y = y * s;
}

float df::Vector::getMagnitude() const { return sqrt(x * x + y * y); }

df::Vector df::Vector::operator+(const Vector& other) const {
	Vector v;			// Create new vector.
	v.x = x + other.x;	// Add x components.
	v.y = y + other.y;	// Add y components.
	return v;			// Return new vector.
}

df::Vector df::Vector::operator-(const Vector& other) const {
	Vector v;			// Create new vector.
	v.x = x - other.x;	// Add x components.
	v.y = y - other.y;	// Add y components.
	return v;			// Return new vector.
}

bool df::Vector::operator==(const Vector& other) const {return other.x == getX() && other.y == getY();}