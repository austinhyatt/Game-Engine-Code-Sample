#include "Utility.h"
#include "WorldManager.h"
#include <cmath>

// Return true if two positions intersect, else false.
bool df::positionsIntersect(df::Vector p1, df::Vector p2) {
	return (abs(p1.getX() - p2.getX()) <= 1 && abs(p1.getY() - p2.getY()) <= 1);
}

bool df::boxIntersectsBox(Box box1, Box box2)
{
	bool horiz_overlap = (box1.getCorner().getX() <= box2.getCorner().getX() && box2.getCorner().getX() <= box1.getCorner().getX() + box1.getHorizontal()) //horiz b2 in b1
				      || (box2.getCorner().getX() <= box1.getCorner().getX() && box1.getCorner().getX() <= box2.getCorner().getX() + box2.getHorizontal()); //horiz b1 in b2
	bool vert_overlap = (box1.getCorner().getY() <= box2.getCorner().getY() && box2.getCorner().getY() <= box1.getCorner().getY() + box1.getVertical()) //vert b2 in b1
				     || (box2.getCorner().getY() <= box1.getCorner().getY() && box1.getCorner().getY() <= box2.getCorner().getY() + box2.getVertical()); //vert b1 in b2
	return horiz_overlap && vert_overlap;
}

df::Box df::getWorldBox(const Object* o, Vector where)
{
	Box temp_box = o->getBox();
	Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + where.getX());
	corner.setY(corner.getY() + where.getY());
	temp_box.setCorner(corner);

	return temp_box;
}

df::Box df::getWorldBox(const Object* o) {return getWorldBox(o, o->getPosition());}

df::Vector df::worldToView(Vector world_pos)
{
	Vector view_origin = WM.getView().getCorner();
	return Vector(world_pos.getX() - view_origin.getX(), world_pos.getY() - view_origin.getY());
}

df::Vector df::viewToWorld(Vector world_pos)
{
	Vector view_origin = WM.getView().getCorner();
	return Vector(world_pos.getX() + view_origin.getX(), world_pos.getY() + view_origin.getY());
}
