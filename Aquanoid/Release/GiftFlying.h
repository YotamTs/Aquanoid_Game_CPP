#pragma once
#include "Gift.h"

//=-------------------------------------------GiftFlying.h----------------------------------------=//

class GiftFlying :
	public Gift
{
public:

	GiftFlying(sf::RenderWindow& win , sound_t sound_index , texture_t texture_index , float x , float y)
		:Gift(win , sound_index , texture_index , x , y)
	{
		_sound.setBuffer(getSound(sound_index));
		_sprite.setTextureRect(sf::IntRect(534 , 468 , 103 , 28));

		_sprite.setPosition(x , y);
	}

	virtual ~GiftFlying()
	{}

	void collide(const GameObject* gameObjectP , Controller& con)
	{
		if( !_activate )
		{
			Paddle *paddle = (Paddle*) gameObjectP;
			paddle->setFlying(true);
			_activate = true;
		}
		_giftTaken = true;
	}
};

