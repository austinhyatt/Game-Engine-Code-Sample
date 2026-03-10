#ifndef OBJECT_LIST_ITERATOR_H
#define OBJECT_LIST_ITERATOR_H

#include "Object.h"
#include "ObjectList.h"

namespace df {

	class ObjectList;

	class ObjectListIterator {

	private:
		ObjectListIterator();	// Iterator must be given list when created.
		int index;				// Index into list.
		const ObjectList* list;	// List iterating over.

	public:
		// Create iterator, over indicated list.
		ObjectListIterator(const ObjectList* objList);

		// Set iterator to first item in list.
		void first();

		// Set iterator to next item in list.
		void next();

		// Return true if at end of list.
		bool hasNext() const;

		// Return pointer to current item in list, NULL if done/empty.
		Object* currentObject() const;
	};

}
#endif
