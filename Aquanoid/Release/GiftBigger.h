#pragma once

#include "Gift.h"
//=-------------------------------------------OneLifeGift.h----------------------------------------=//

class GiftBigger :
	public Gift
{
public:

	GiftBigger(sf::RenderWindow& win , sound_t sound_index , texture_t texture_index , float x , float y)
		:Gift(win , sound_index , texture_index , x , y)
	{
		_sound.setBuffer(getSound(sound_index));
		_sprite.setTextureRect(sf::IntRect(385 , 448 , 64 , 15));

		_sprite.setPosition(x , y);
	}
	//---------------------------------------------------------

	virtual ~GiftBigger(){}
	//---------------------------------------------------------

	void collide(const GameObject* gameObjectP , Controller& con)
	{
		if( !_activate )
		{
			Paddle *paddle = (Paddle*) gameObjectP;
			if( paddle->getScaleX() < 3.8f )
			{
				paddle->scale(1.25 , 1);
				_activate = true;
			}
		}
		_giftTaken = true;
	}
};

