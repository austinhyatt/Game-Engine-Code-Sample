#include "ObjectListIterator.h"
#include "ObjectList.h"
#include "Object.h"

df::ObjectListIterator::ObjectListIterator(const ObjectList* objList) {
	list = objList;
	first();
}

void df::ObjectListIterator::first() { index = 0; }

void df::ObjectListIterator::next() {
	if (index < list->count)
		index++;
}

bool df::ObjectListIterator::hasNext() const { return index == list->count; }

df::Object* df::ObjectListIterator::currentObject() const { return list->obj[index]; }