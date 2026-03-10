#include "WorldManager.h"
#include "ObjectListIterator.h"
#include "LogManager.h"
#include "Utility.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "ViewObject.h"

df::WorldManager::WorldManager() {
	setType("worldmanager");

	updates = df::ObjectList();
	deletions = df::ObjectList();

	boundary = Box();
	view = Box();

	startUp();

	LM.writeLog("WorldManager constructed");
}


int df::WorldManager::startUp() {
	updates.clear();
	deletions.clear();
	return 0;
}

void df::WorldManager::shutDown() {
	//delete all game world objects
	ObjectListIterator li(&updates);
	for (li.first(); !li.hasNext(); li.next())
		delete li.currentObject();

	LM.writeLog("WorldManager destructed");
}

df::WorldManager& df::WorldManager::getInstance() {
	static df::WorldManager s_worldManager;
	return s_worldManager;
}


int df::WorldManager::insertObject(Object* o) { 
	updates.insert(o); 
	return 0;
}


int df::WorldManager::removeObject(Object* o) {
	updates.remove(o); 
	return 0;
}

df::ObjectList df::WorldManager::getAllObjects() const { return updates; }

df::ObjectList df::WorldManager::getAllObjectsOfType(std::string type) const {
	ObjectList out = ObjectList();
	ObjectListIterator updatesIter = ObjectListIterator(&updates);

	for (updatesIter.first(); !updatesIter.hasNext(); updatesIter.next())
		if (updatesIter.currentObject()->getType() == type)
			out.insert(updatesIter.currentObject());
	return out;
}

int df::WorldManager::markForDelete(Object* o) {
	ObjectListIterator li = ObjectListIterator(&deletions);
	for (li.first(); !li.hasNext(); li.next())
		if (li.currentObject() == o)
			return -1;
	

	deletions.insert(o);
	return 0;
}

void df::WorldManager::update() {
	//remove objects marked for deletion
	ObjectListIterator dli(&deletions);
	for (dli.first(); !dli.hasNext(); dli.next())
		delete dli.currentObject();
	deletions.clear();

	//update obj positions based on velocities
	ObjectListIterator uli(&updates);
	for (uli.first(); !uli.hasNext(); uli.next()) {
		Vector new_pos = uli.currentObject()->predictPosition();
		//printf("obj current pos %.f, %.f\tobj predict pos %.f, %.f\n", uli.currentObject()->getPosition().getX(), uli.currentObject()->getPosition().getY(), new_pos.getX(), new_pos.getY());
		if (new_pos.getX() != uli.currentObject()->getPosition().getX() ||
			new_pos.getY() != uli.currentObject()->getPosition().getY()) {
			moveObject(uli.currentObject(), new_pos);
		}
	}
}

void df::WorldManager::draw() {
	ObjectListIterator updatesIter = ObjectListIterator(&updates);
	for(int alt = 0; alt <= MAX_ALTITUDE; alt++)
		for (updatesIter.first(); !updatesIter.hasNext(); updatesIter.next())
			if((updatesIter.currentObject()->getAltitude() == alt 
				/*&& boxIntersectsBox(updatesIter.currentObject()->getBox(), view)*/)
				|| (dynamic_cast <ViewObject *> (updatesIter.currentObject())))
				updatesIter.currentObject()->draw();
}

df::ObjectList df::WorldManager::getCollisions(const Object* o, Vector where) const {

	// Make empty list.
	ObjectList collision_list;

	// Iterate through all objects.
	ObjectListIterator li = ObjectListIterator(&updates);
	for (li.first(); !li.hasNext(); li.next()) {
		Object* temp_o = li.currentObject();
		if (temp_o != o) { // Do not consider self.
			Box b = getWorldBox(o, where);
			Box b_temp = getWorldBox(temp_o);
			// Same location and both solid?
			if (df::boxIntersectsBox(b, b_temp) && temp_o->isSolid())
				collision_list.insert(temp_o);
		}
	}

	return collision_list;
}

int df::WorldManager::moveObject(Object* o, Vector where) {
	if(o->isSolid()) { // Need to be solid for collisions.
	  // Get collisions.
		ObjectList list = getCollisions(o, where);
		if(list.getCount()>0)
		if (!list.isEmpty()) {
			bool do_move = true;  // Assume can move.
			// Iterate over list.
				ObjectListIterator li = ObjectListIterator(&list);
				for (li.first(); !li.hasNext(); li.next()) {
					Object* temp_o = li.currentObject();
					// Create collision event.
					EventCollision c = EventCollision(o, temp_o, where);
					// Send to both objects.
					o->eventHandler(&c);
					temp_o->eventHandler(&c);

						// If both HARD, then cannot move.
					if (o->getSolidness() == HARD && temp_o->getSolidness() == HARD)
						do_move = false;  // Can't move.
				}
				if (!do_move)
					return -1; // Move not allowed.
		}
	}
	// do move
	Box orig_box = getWorldBox(o);
	o->setPosition(where);
	Box new_box = getWorldBox(o);
	//is object out of bounds?
	if (boxIntersectsBox(orig_box, boundary)&& !boxIntersectsBox(new_box, boundary)) {
		EventOut e = EventOut();
		o->eventHandler(&e);
	}
	//if view is following this obj, adjust view
	if (view_following == o)
		setViewPosition(o->getPosition());
	// All is well.
	return 0; // Move was ok.
}

void df::WorldManager::setBoundary(Box new_boundary) { boundary = new_boundary; }

df::Box df::WorldManager::getBoundary() const { return boundary; }

void df::WorldManager::setView(Box new_view) { view = new_view; }

df::Box df::WorldManager::getView() const { return view; }

void df::WorldManager::setViewPosition(Vector view_pos)
{
	int x = view_pos.getX() - view.getHorizontal() / 2;
	if (x + view.getHorizontal() > boundary.getHorizontal())
		x = boundary.getHorizontal() - view.getHorizontal();
	if (x < 0)
		x = 0;
	int y = view_pos.getY() - view.getVertical() / 2;
	if (y + view.getVertical() > boundary.getVertical())
		y = boundary.getVertical() - view.getVertical();
	if (y < 0)
		y = 0;
	view.setCorner(Vector(x, y));
}

int df::WorldManager::setViewFollowing(Object* new_view_following)
{
	if (new_view_following == NULL) {
		new_view_following = NULL;
		return 0;
	}

	ObjectList ol = WM.getAllObjects();
	ObjectListIterator li(&ol);
	for (li.first(); !li.hasNext(); li.next()) {
		if (li.currentObject() == new_view_following) {
			view_following = new_view_following;
			setViewPosition(view_following->getPosition());
			return 0;
		}
	}
	return -1;
}
