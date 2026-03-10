#ifndef _RAIL_
#define _RAIL_
#include "Object.h"
#include "Event.h"
#include "Vector.h"
#include "Color.h"

class Rail : public df::Object {
	private:
		df::Vector spawnLocation;
		df::Color scrambleColor;
		int spawnTimer;
		int difficulty;
		float speed;
		Rail* otherRail1;
		Rail* otherRail2;
	public:
		int direction;
		df::Color lastColor;
		df::Color secondLastColor;

		Rail(df::Vector v, int dir, int diff);
		int eventHandler(const df::Event* event) override;
		void spawnObstacle(int length, float speed, df::Color color);
		df::Color getRandomColor(df::Color bannedColor, bool scramble = false);
		void setOtherRails(Rail* r1, Rail* r2);
};
#endif