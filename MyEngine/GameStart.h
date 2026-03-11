#ifndef _GAME_START_H_
#define _GAME_START_H_

#include "Object.h"
#include "Event.h"
#include "EventStep.h"
#include "Color.h"

class GameStart : public df::Object {
private:
	int m_color;
	int m_difficulty;
	df::Color m_tutorialherocolor;
public:
	GameStart();

	int eventHandler(const df::Event* p_e) override;

	void step(int step);

	void setColorCount(int new_color);

	void startGame();
};

#endif