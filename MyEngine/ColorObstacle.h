#ifndef _COLOROBSTACLE_
#define _COLOROBSTACLE_

#include "Object.h"
#include "Color.h"
#include "Event.h"

class ColorObstacle : public df::Object {
	private:
		std::string str;
	public:
		int length;
		df::Color color;

		ColorObstacle(df::Vector pos, int l, float s, df::Color c);

		int eventHandler(const df::Event* event) override;

		int draw() override;
};
#endif

