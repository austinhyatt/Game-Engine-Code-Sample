#include <string>

#include "Manager.h"
#include "WorldManager.h"

df::Manager::Manager() {
	m_type = "null";
	is_started = false;
	startUp();
}

int df::Manager::startUp() {
	is_started = true;
	return 0;
}

df::Manager::~Manager() {
	shutDown();
}

void df::Manager::shutDown() {
	is_started = false;
}

std::string df::Manager::getType() const {
	return m_type;
}

void df::Manager::setType(std::string new_type) {
	m_type = new_type;
}

bool df::Manager::isStarted() const {
	return is_started;
}

int df::Manager::onEvent(const Event* p_event) const {
	df::ObjectList all_objects = WM.getAllObjects();
	df::ObjectListIterator li = df::ObjectListIterator(&all_objects);
	for (li.first(); !li.hasNext(); li.next())
		li.currentObject()->eventHandler(p_event);
	return all_objects.getCount();
}