#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "Object.h"
#include "ObjectListIterator.h"

namespace df {

	const int MAX_OBJECTS = 5000;

	class ObjectListIterator;

	class ObjectList {

	private:
		int count;                    // Count of objects in list.
		Object* obj[MAX_OBJECTS];   // Array of pointers to objects.

	public:
		friend class ObjectListIterator;           // Iterators can access.

		// Default constructor.
		ObjectList();

		// Insert object pointer in list.
		// Return 0 if ok, else -1.
		int insert(Object* o);

		// Remove object pointer from list,
		// Return 0 if found, else -1.
		int remove(Object* o);

		// Clear list (setting count to 0).
		void clear();

		// Return count of number of objects in list.
		int getCount() const;

		// Return true if list is empty, else false.
		bool isEmpty() const;

		// Return true if list is full, else false.
		bool isFull() const;
	};

}
#endif