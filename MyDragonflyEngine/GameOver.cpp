#include "GameOver.h"
#include "GameStart.h"
#include "ResourceManager.h"
#include "EventKeyboard.h"



GameOver::GameOver(int initial_step) {
	m_initial_step = initial_step;
	m_time_to_live = 30 * 2.5;
	color = 0;

	setPosition(df::Vector(DM.getHorizontal()/2 + 2, DM.getVertical()/2));
	setSprite("gameover");
	setAltitude(df::MAX_ALTITUDE);
}

GameOver::~GameOver() {
	df::ObjectList list = WM.getAllObjects();
	df::ObjectListIterator li(&list);
	for (li.first(); !li.hasNext(); li.next()) {
		WM.markForDelete(li.currentObject());
	}
	RM.getMusic("gamemusic")->stop();
	new GameStart;
}

int GameOver::eventHandler(const df::Event* p_e) {
	DM.drawString(df::Vector(DM.getHorizontal() / 2 + 2, DM.getVertical()-2), "Press SPACE to skip", df::CENTER_JUSTIFIED, df::WHITE);
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_s =
			dynamic_cast <const df::EventStep*> (p_e);
		step(p_s->getStepCount());
		return 1;
	}
	if (p_e->getType() == df::KBD_EVENT) {
		const df::EventKeyboard* p_kbd =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_kbd->getKey() == df::Keyboard::SPACE) {
			WM.markForDelete(this);
		}
	}
	return 0;
}

void GameOver::step(int current_step) {
	if (((current_step - m_initial_step) % m_time_to_live) == 0) {
		WM.markForDelete(this);
	}
	if (current_step % 15 == 0) {
		if (color == 0) {
			getAnimation().getSprite()->setColor(df::Color::CYAN);
			setColorCount(1);
			return;
		}
		if (color == 1) {
			getAnimation().getSprite()->setColor(df::Color::RED);
			setColorCount(2);
			return;
		}
		if (color == 2) {
			getAnimation().getSprite()->setColor(df::Color::YELLOW);
			setColorCount(0);
			return;
		}
	}
}

void GameOver::setColorCount(int new_color) {
	color = new_color;
}