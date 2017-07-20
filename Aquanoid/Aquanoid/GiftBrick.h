#pragma once

#include "Brick.h"
#include "Controller.h"

//=-------------------------------------------GiftBrick.h----------------------------------------=//
class GiftBrick : public Brick
{
public:

	GiftBrick(sf::RenderWindow& win , sound_t sound , texture_t texture , std::pair<int , int> pos)
		:Brick(win , sound , texture,pos){}

	virtual ~GiftBrick(){}

	//---------------------------------------------------------
	virtual void collide(const GameObject* gameObjectP , Controller& con)
	{
			play_sound();
			destroy(con);
		    auto a = _sprite.getPosition().x + _sprite.getGlobalBounds().width / 2;
			auto b = _sprite.getPosition().y + _sprite.getGlobalBounds().height;
			con.addGift(a,b);
			con.scoreUpdate(30);

		Ball *ballP = (Ball*) gameObjectP;
		ballUpdate(ballP);
	}
};