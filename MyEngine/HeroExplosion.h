#ifndef _HEROEXPLOSION_H_
#define _HEROEXPLOSION_H_


#include "Object.h"
class HeroExplosion : public df::Object {
private:
	int m_timetolive;
public:
	HeroExplosion(df::Vector pos);
	~HeroExplosion();

	int eventHandler(const df::Event* p_e) override;

	void step();
};

#endif // !_HEROEXPLOSION_H_