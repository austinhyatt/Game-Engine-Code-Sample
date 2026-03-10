#ifndef UTILITY_H
#define UTILITY_H

// Engine includes
//#include "Box.h"
#include "EventKeyboard.h"
#include "Object.h"
#include "Vector.h"

namespace df {
	bool positionsIntersect(Vector p1, Vector p2);
	// Return true if Boxes intersect.
	bool boxIntersectsBox(Box box1, Box box2);
	// Convert relative bounding Box for Object to absolute world Box.
	Box getWorldBox(const Object* o);
	// Convert relative bounding Box for Object to absolute world Box
	// at postion where.
	Box getWorldBox(const Object* o, Vector where);
	//Convert world pos to view pos
	Vector worldToView(Vector world_pos);
	//Convert world pos to view pos
	Vector viewToWorld(Vector world_pos);
}
#endif