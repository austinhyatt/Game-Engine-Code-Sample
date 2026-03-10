#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

// System includes.
#include <string>

// Engine includes.
#include "Event.h"
#include "Object.h"

namespace df {

	class TestObject : public Object {

	public:
		TestObject();
		int eventHandler(const Event* event) override;
		int step;
		int draw() override;

		bool outOfBounds;
		bool collided;
	};

}
#endif
