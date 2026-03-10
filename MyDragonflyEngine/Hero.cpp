#include <sstream>
#include "Hero.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "ColorObstacle.h"
#include "ResourceManager.h"
#include "WallObstacle.h"
#include "Utility.h"
#include "HighScore.h"
#include "HeroExplosion.h"

Hero::Hero(int difficulty) {
	m_difficulty = difficulty;
	m_location = 0;
	m_movevertical_slowdown = 6;
	m_movevertical_countdown = m_movevertical_slowdown;
	m_points = 0;
	m_starCount = 0;
	m_damagesound_slowdown = 3;
	m_damagesound_countdown = m_damagesound_slowdown;
	m_isIntensityOn = false;
	RM.getMusic("gamemusic")->getMusic()->setPitch(1);

	switch (difficulty) {
	case 1:
		m_health = 120; // Default 100
		break;
	case 2:
		m_health = 90;
		RM.getMusic("gamemusic")->getMusic()->setPitch(1.05f);
		break;
	case 3:
		m_health = 60;
		RM.getMusic("gamemusic")->getMusic()->setPitch(1.1f);
		break;
	case 4:
		m_health = 5;
		m_isIntensityOn = true;
		RM.getMusic("gamemusic")->getMusic()->setPitch(1.2f);
		break;
	}
	m_max_health = m_health;


	setPosition(df::Vector(DM.getHorizontal()/2.0, DM.getVertical()/2.0));
	setSprite("herol");
	setAltitude(df::MAX_ALTITUDE);
	setType("hero");
	setSolidness(df::HARD);
}

Hero::~Hero() {
	HighScore highscore = HighScore(m_difficulty);
	highscore.setHighScore(m_points);
	new HeroExplosion(this->getPosition());
	RM.getMusic("gamemusic")->getMusic()->stop();
}

int Hero::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::KBD_EVENT) { // Keyboard events
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c = dynamic_cast <const df::EventCollision*> (p_e);

		Object* hero = p_c->getObject1()->getType() == "hero" ? p_c->getObject1() : p_c->getObject2();
		Object* other = p_c->getObject1() == hero ? p_c->getObject2() : p_c->getObject1();

		// If player collides with color obstacle
		if (other->getType() == "colorobstacle") { // Color obstacle needs a get color method
			if (starTimer > 0)
				return 1;
			const ColorObstacle* otherColor = dynamic_cast <const ColorObstacle*> (other);
			if (!(getAnimation().getSprite()->getColor() == otherColor->color)) {
				m_health--;
				if (!(m_damagesound_countdown > 0)) {
					RM.getSound("damage")->play();
					m_damagesound_countdown = m_damagesound_slowdown;
				}
				//printf("Object hero color: %d\n Object 2 color: %d\n",
					//p_c->getObject1()->getAnimation().getSprite()->getColor(), obj2->color);
				//printf("Health %d\n", m_health);
			}
		}

		// If player collides with border
		if (other->getType() == "border") {
			//Can't get pushed through borders
			if (getPosition().getX() < 7) {
				setPosition(df::Vector(7, getPosition().getY()));
				setVelocity(df::Vector());
			}
			else if (getPosition().getX() > DM.getHorizontal() - 3) {
				setPosition(df::Vector(DM.getHorizontal() - 3, getPosition().getY()));
				setVelocity(df::Vector());
			}
			//damage sound
			if (!(m_damagesound_countdown > 0)) {
				RM.getSound("damage")->play();
				m_damagesound_countdown = m_damagesound_slowdown;
			}
			m_health--;
		}

		if (other->getType() == "wallobstacle") {
			const WallObstacle* otherWall = dynamic_cast <const WallObstacle*> (other);
			df::Vector move = getPosition() + otherWall->getVelocity() - getVelocity();
			//if move will stick in wall
			if (df::boxIntersectsBox(getBox(), other->getBox()) && m_movevertical_countdown == m_movevertical_slowdown - 1) {
				df::Box b = df::Box(getBox().getCorner()+getVelocity(), getBox().getHorizontal(), getBox().getVertical());
				int i = 1;
				while (true) {
					b.setCorner(df::Vector(getBox().getCorner().getX() + i, getBox().getCorner().getY()));
					if (!df::boxIntersectsBox(b, other->getBox())) {
						move = move + df::Vector(i + 2, 0);
						break;
					}
					b.setCorner(df::Vector(getBox().getCorner().getX() - i, getBox().getCorner().getY()));
					if (!df::boxIntersectsBox(b, other->getBox())) {
						move = move + df::Vector(-i - 2, 0);
						break;
					}
					i++;
				}
			}
			//crushed
			if ((getPosition().getX() - (getAnimation().getSprite()->getLabel() == "herol" ? 1 : 0) < 7 && getPosition().getX()<other->getPosition().getX())
				|| (getPosition().getX() + (getAnimation().getSprite()->getLabel() == "heror" ? 1 : 0) > DM.getHorizontal() - 4 && getPosition().getX() > other->getPosition().getX()))
				m_health = 0;
			else
				setPosition(move);
		}

		if (other->getType() == "star") {
			if (m_starCount < 5 && starTimer == 0 && other->getId() != lastStarId) {
				m_starCount++;
				lastStarId = other->getId();
				//printf("starcount %i\n", m_starCount);
			}
			if (starTimer > 0) starTimer += 18;
			WM.markForDelete(other);
		}
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_s =
			dynamic_cast <const df::EventStep*> (p_e);
		if (m_health <= 0) {
			WM.markForDelete(this);
		}
		step();
		return 1;
	}

	return 0;
}

void Hero::kbd(const df::EventKeyboard* p_ke) {
	df::Color c = getAnimation().getSprite()->getColor();
	switch (p_ke->getKey()) {

		// Quit
	case df::Keyboard::Q:
		m_health = 0;
		break;

		// Move Up
	case df::Keyboard::UPARROW:
		moveVertical(+1);
		break;

		// Move Down
	case df::Keyboard::DOWNARROW:
		moveVertical(-1);
		break;

		// Move Left
	case df::Keyboard::LEFTARROW:
		setSprite("herol");
		getAnimation().getSprite()->setColor(c);
		moveHorizontal(-1.0);
		break;

		// Move Right
	case df::Keyboard::RIGHTARROW:
		setSprite("heror");
		getAnimation().getSprite()->setColor(c);
		moveHorizontal(+1.0);
		break;

		// Change Color red cyan yellow
	case df::Keyboard::Z:
		if (starTimer > 0) return;
		colorShift(df::Color::RED);
		break;
	case df::Keyboard::X:
		if (starTimer > 0) return;
		colorShift(df::Color::CYAN);
		break;
	case df::Keyboard::C:
		if (starTimer > 0) return;
		colorShift(df::Color::YELLOW);
		break;
	case df::Keyboard::SPACE:
		if (m_starCount < 5)
			return;
		m_starCount = 0;
		if(c!=df::MAGENTA)
			starLastUsedColor = c; // color to swap back to once star is active
		starTimer = 180;
		getAnimation().getSprite()->setColor(df::MAGENTA);
	}
}

void Hero::moveVertical(int direction) {
	if (m_movevertical_countdown > 0) return;
	switch (m_location) {
		// At top rail
	case 1:
		if (direction == +1) { return; }
		m_movevertical_countdown = m_movevertical_slowdown;
		m_location = 0;
		setPosition(df::Vector(getPosition().getX(), MID_RAIL));
		return;

		// At Mid rail
	case 0:
		m_movevertical_countdown = m_movevertical_slowdown;
		if (direction == +1) {
			m_location = 1;
			setPosition(df::Vector(getPosition().getX(), TOP_RAIL));
			return;
		}
		if (direction == -1) {
			m_location = -1;
			setPosition(df::Vector(getPosition().getX(), BOT_RAIL));
			return;
		}
		break;

		// At Bottom rail
	case -1:
		if (direction == -1) { return; }
		m_movevertical_countdown = m_movevertical_slowdown;
		m_location = 0;
		setPosition(df::Vector(getPosition().getX(), MID_RAIL));
		return;
	}
}

void Hero::moveHorizontal(float dx) {
	setVelocity(df::Vector(dx*.75*1.38, 0));
}

void Hero::colorShift(df::Color color) {

	getAnimation().getSprite()->setColor(color);
}

void Hero::step() {
	m_movevertical_countdown--;
	if (m_movevertical_countdown < 0) m_movevertical_countdown = 0;
	m_damagesound_countdown--;
	if (m_damagesound_countdown < 0) m_damagesound_countdown = 0;

	if (getAnimation().getSprite()->getColor() == df::MAGENTA)
		if (starTimer > 0)
			starTimer--;
		else
			getAnimation().getSprite()->setColor(starLastUsedColor);

	// Star function
	std::string star_bar = "[";
	for (int i = 0; i < m_starCount; i++) {
		star_bar.append("||");
	}

	for (int i = 0; i < 5 - m_starCount; i++) {
		star_bar.append("  ");
	}
	star_bar.append("]");

	if (m_starCount == 5) star_bar = "[||||||||||] Press Space!";

	if (starTimer > 0) {
		if (starTimer > 18) star_bar =  "[|         ]";
		if (starTimer > 36) star_bar =  "[||        ]";
		if (starTimer > 54) star_bar =  "[|||       ]";
		if (starTimer > 72) star_bar =  "[||||      ]";
		if (starTimer > 90) star_bar =  "[|||||     ]";
		if (starTimer > 108) star_bar = "[||||||    ]";
		if (starTimer > 126) star_bar = "[|||||||   ]";
		if (starTimer > 144) star_bar = "[||||||||  ]";
		if (starTimer > 162) star_bar = "[||||||||| ]";
	}


	m_points++;

	std::string health_bar = "HP: [";
	std::string points = "Score: ";

	// Points function
	std::stringstream ss;
	ss << m_points;
	points.append(ss.str());

	// Health function
	for (int i = 0; i < (int) m_health / 4; i++) { 
		health_bar.append("|");
	}
	health_bar.append("]");

	if (m_health < 4) health_bar = "HP: [|]";

	DM.drawString(df::Vector(4, DM.getVertical() / 2 - 7), health_bar, df::LEFT_JUSTIFIED, df::YELLOW);
	DM.drawString(df::Vector(DM.getHorizontal(), DM.getVertical() / 2 - 7), points, df::RIGHT_JUSTIFIED, df::YELLOW);
	DM.drawString(df::Vector(DM.getHorizontal()/2, DM.getVertical() / 2 + 7), star_bar, df::CENTER_JUSTIFIED, df::MAGENTA);
	//zxc
	DM.drawString(df::Vector(4, DM.getVertical() / 2 + 7), "[Z]", df::LEFT_JUSTIFIED, df::RED);
	DM.drawString(df::Vector(8, DM.getVertical() / 2 + 7), "[X]", df::LEFT_JUSTIFIED, df::CYAN);
	DM.drawString(df::Vector(12, DM.getVertical() / 2 + 7), "[C]", df::LEFT_JUSTIFIED, df::YELLOW);

	if (m_health < (m_max_health / 3) && !m_isIntensityOn) { // Increases pitch intensity by 10% when health is below half
		RM.getMusic("gamemusic")->getMusic()->setPitch(RM.getMusic("gamemusic")->getMusic()->getPitch() + .1f);
		m_isIntensityOn = true;
	}
}

