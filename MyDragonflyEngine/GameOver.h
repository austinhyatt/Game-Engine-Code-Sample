#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "Object.h"
#include "WorldManager.h"
#include "EventStep.h"

class GameOver : public df::Object {
private:
	int m_initial_step;
	int m_time_to_live;
	int color;

	void step(int current_step);

	void setColorCount(int new_color);

public:
	GameOver(int initial_step);

	~GameOver();

	int eventHandler(const df::Event* p_e) override;
};

#endif