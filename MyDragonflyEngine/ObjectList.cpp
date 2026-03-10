#include "ObjectList.h"

df::ObjectList::ObjectList() {
	count = 0;
}

int df::ObjectList::insert(Object* o) {
	if (!isFull()) {
		obj[count] = o;
		count++;
		return 0;
	}
	return -1;
}

void df::ObjectList::clear() {
	for (int i = 0; i <= count; i++)
		obj[i] = NULL;
	count = 0;
}

int df::ObjectList::remove(Object* o) {
	for (int i = 0; i < count; i++) {
		if (obj[i] == o) { //found
			for (int j = i; j < count - 1; j++) // scoot over
				obj[j] = obj[j + 1];
			count--;
			return 0; //found
		}
	}
	return -1; // Not found
}

int df::ObjectList::getCount() const { return count; }

bool df::ObjectList::isEmpty() const { return count <= 0; }

bool df::ObjectList::isFull() const { return count >= MAX_OBJECTS; }