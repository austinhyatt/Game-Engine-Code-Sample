#include "HeroExplosion.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "GameOver.h"
#include "ResourceManager.h"

HeroExplosion::HeroExplosion(df::Vector pos) {
	setSolidness(df::SPECTRAL);
	setAltitude(df::MAX_ALTITUDE);
	if (!setSprite("heroexplode")) m_timetolive = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	else m_timetolive = 0;

	setPosition(pos);
	RM.getSound("explosion")->play();
	
}

HeroExplosion::~HeroExplosion() {
}

int HeroExplosion::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_s =
			dynamic_cast <const df::EventStep*> (p_e);
		m_timetolive--;
		if (m_timetolive <= 0) {
			WM.markForDelete(this);
			new GameOver(p_s->getStepCount());
		}
		return 1;
	}

	return 0;
}

void HeroExplosion::step() {
	m_timetolive--;
	if (m_timetolive <= 0) WM.markForDelete(this);
}
