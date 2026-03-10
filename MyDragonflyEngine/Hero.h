#ifndef _HERO_H_
#define _HERO_H_
#include "Object.h"
#include "EventKeyboard.h"
#include "Color.h"

class Hero : public df::Object {

	const float TOP_RAIL = DM.getVertical() / 2 - 4;
	const float MID_RAIL = DM.getVertical() / 2;
	const float BOT_RAIL = DM.getVertical() / 2 + 4;

private:
	int m_location = 0;		// Current location of the hero, used to dictate where to move
	int m_health = 100;
	int m_max_health = m_health;
	int m_movevertical_slowdown = 10;
	int m_movevertical_countdown = m_movevertical_slowdown;
	int m_damagesound_slowdown = 4;
	int m_damagesound_countdown = m_damagesound_slowdown;
	int m_difficulty;
	unsigned long long m_points = 0;
	bool m_isIntensityOn = false;
	int m_starCount;

	df::Color starLastUsedColor;
	int starTimer;
	int lastStarId;

	// keyboard
	void kbd(const df::EventKeyboard* p_ke);

	// takes in current location and direction. + for up, - for down
	void moveVertical(int direction);

	void moveHorizontal(float dx);

	void colorShift(df::Color color);

	void step();

public:

	// Hero Constructor
	Hero(int difficulty);

	// Hero Destructor
	~Hero();

	// event Handler
	int eventHandler(const df::Event* p_e) override;
};

#endif