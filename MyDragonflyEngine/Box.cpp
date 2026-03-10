#include "Box.h"

df::Box::Box()
{
	corner = Vector(0, 0);
	horizontal = 0;
	vertical = 0;
}

df::Box::Box(Vector init_corner, float init_horizontal, float init_vertical)
{
	corner = init_corner;
	horizontal = init_horizontal;
	vertical = init_vertical;
}

void df::Box::setCorner(Vector new_corner) {corner = new_corner;}

df::Vector df::Box::getCorner() const {return corner;}

void df::Box::setHorizontal(float new_horizontal) {horizontal = new_horizontal;}

float df::Box::getHorizontal() const {return horizontal;}

void df::Box::setVertical(float new_vertical) {vertical = new_vertical;}

float df::Box::getVertical() const {return vertical;}



