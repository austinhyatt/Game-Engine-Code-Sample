#include "GameStart.h"
#include "EventKeyboard.h"
#include "Hero.h"
#include "Rail.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "WallObstacle.h"
#include "HighScore.h"
#include "Star.h"
#include <sstream>

GameStart::GameStart() {
	srand(time(NULL));
	m_color = 0;
	m_difficulty = 1;
	m_tutorialherocolor = df::RED;

	setSprite("gamestart");
	setAltitude(3);
	setPosition(df::Vector(DM.getHorizontal() / 2 + 2, 7));
}

int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_s =
			dynamic_cast <const df::EventStep*> (p_e);
		step(p_s->getStepCount());
		return 1;
	}
	if (p_e->getType() == df::KBD_EVENT) {
		const df::EventKeyboard* p_ke =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_ke->getKey() == df::Keyboard::P) {
			startGame();
		}
		if (p_ke->getKey() == df::Keyboard::Q) {
			GM.setGameOver();
		}
		if (p_ke->getKey() == df::Keyboard::R) {
			HighScore temp = HighScore(m_difficulty);
			temp.resetHighScore();
		}

		if (p_ke->getKey() == df::Keyboard::Z) {
			m_tutorialherocolor = df::RED;
		}
		if (p_ke->getKey() == df::Keyboard::X) {
			m_tutorialherocolor = df::CYAN;
		}
		if (p_ke->getKey() == df::Keyboard::C) {
			m_tutorialherocolor = df::YELLOW;
		}

		if (p_ke->getKey() == df::Keyboard::NUM1) { // normal settings now
			m_difficulty = 1;
		}
		if (p_ke->getKey() == df::Keyboard::NUM2) { // less health and faster
			m_difficulty = 2;
		}
		if (p_ke->getKey() == df::Keyboard::NUM3) { // lesser health and fasterer
			m_difficulty = 3;
		}
		if (p_ke->getKey() == df::Keyboard::NUM4) { // maybe one shot kill? faster?
			m_difficulty = 4;
		}
		return 1;
	}
	return 0;
}

void GameStart::step(int step) {
	// Difficulty string switch case:
	std::string difficulty = "Current difficulty: ";
	df::Color color{};
	switch (m_difficulty) {
	case 1:
		color = df::CYAN;
		difficulty.append("Baby Blue");
		break;
	case 2:
		color = df::GREEN;
		difficulty.append("Fair Green");
		break;
	case 3:
		color = df::MAGENTA;
		difficulty.append("Hot Magenta");
		break;
	case 4:
		color = df::RED;
		difficulty.append("Blood Red");
		break;
	}

	HighScore highscore = HighScore(m_difficulty);
	unsigned long long score = highscore.getHighScore();
	std::stringstream ss;
	ss << score;
	std::string highscore_str = "High Score: ";
	highscore_str.append(ss.str());
	DM.drawString(df::Vector(DM.getHorizontal() / 2 + 2, 15), "Press P to start and Q to quit", df::CENTER_JUSTIFIED, df::WHITE);
	DM.drawString(df::Vector(DM.getHorizontal() / 2 + 2, 16), "Use the arrow keys to move", df::CENTER_JUSTIFIED, df::WHITE);	
	DM.drawString(df::Vector(DM.getHorizontal() / 2 + 2, 17), "Press Z, X, and C to change colors. Try it!", df::CENTER_JUSTIFIED, df::WHITE);
	DM.drawString(df::Vector(DM.getHorizontal() / 2 + 2, 18), "Press numbers 1-4 to set difficulty", df::CENTER_JUSTIFIED, df::WHITE);
	DM.drawString(df::Vector(DM.getHorizontal() / 2 + 2, 19), "Press R to current high score", df::CENTER_JUSTIFIED, df::WHITE);
	DM.drawString(df::Vector(DM.getHorizontal() / 2 + 2, 21), difficulty, df::CENTER_JUSTIFIED, color); // Change color of text and string with difficulty
	DM.drawString(df::Vector(DM.getHorizontal() / 2 + 2, 22), highscore_str, df::CENTER_JUSTIFIED, df::YELLOW);

	// Hero drawing function
	DM.drawString(df::Vector(DM.getHorizontal() - 12, 15), " ___ ", df::LEFT_JUSTIFIED, m_tutorialherocolor);
	DM.drawString(df::Vector(DM.getHorizontal() - 12, 16), "/.. \\", df::LEFT_JUSTIFIED, m_tutorialherocolor);
	DM.drawString(df::Vector(DM.getHorizontal() - 12, 17), "(* J)", df::LEFT_JUSTIFIED, m_tutorialherocolor);

	if (step % 15 == 0) {
		if (m_color == 0) {
			getAnimation().getSprite()->setColor(df::Color::CYAN);
			setColorCount(1);
			return;
		}
		if (m_color == 1) {
			getAnimation().getSprite()->setColor(df::Color::RED);
			setColorCount(2);
			return;
		}
		if (m_color == 2) {
			getAnimation().getSprite()->setColor(df::Color::YELLOW);
			setColorCount(0);
			return;
		}
	}
}

void GameStart::setColorCount(int new_color) {
	m_color = new_color;
}

void GameStart::startGame() {
	Hero* hero = new Hero(m_difficulty);

	Rail* r1 = new Rail(df::Vector(DM.getHorizontal() / 2 + 2, DM.getVertical() / 2), -1, m_difficulty);
	Rail* r2 = new Rail(df::Vector(DM.getHorizontal() / 2 + 2, DM.getVertical() / 2 + 4), 1, m_difficulty);
	Rail* r3 = new Rail(df::Vector(DM.getHorizontal() / 2 + 2, DM.getVertical() / 2 - 4), 1, m_difficulty);
	r1->setOtherRails(r2, r3);
	r2->setOtherRails(r1, r3);
	r3->setOtherRails(r1, r2);

	Object* left_border = new Object();
	Object* right_border = new Object();

	left_border->setSprite("border");
	right_border->setSprite("border");

	left_border->setPosition(df::Vector(4.0, DM.getVertical() / 2.0));
	right_border->setPosition(df::Vector(DM.getHorizontal(), DM.getVertical() / 2.0));

	left_border->setAltitude(4);
	right_border->setAltitude(4);

	left_border->setType("border");
	right_border->setType("border");

	RM.getMusic("gamemusic")->play();

	WM.markForDelete(this);
}