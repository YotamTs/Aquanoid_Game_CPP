#pragma once

#include "Brick.h"

//=-------------------------------------------UnbreakableBrick.h----------------------------------------=//
class UnbreakableBrick : public Brick
{
public:

	UnbreakableBrick(sf::RenderWindow& win , sound_t sound , texture_t texture , std::pair<int , int> pos)
		:Brick(win , sound , texture , pos){}

	virtual ~UnbreakableBrick(){}
	//---------------------------------------------------------

	virtual void destroy(Controller& con) { /*  do nothing - Unbreakable.  */}

	//---------------------------------------------------------

	virtual void collide(const GameObject* gameObjectP , Controller& con)
	{
		Ball *ballP = (Ball*) gameObjectP;
		ballUpdate(ballP);
		play_sound();
	}


};

