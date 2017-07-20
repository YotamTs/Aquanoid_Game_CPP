#pragma once

#include "Gift.h"
//=-------------------------------------------BadGift.h----------------------------------------=//
class BadGift :
	public Gift
{
public:

	BadGift(sf::RenderWindow& win , sound_t sound_index , texture_t texture_index , float x , float y) 
		:Gift(win , sound_index , texture_index , x , y)
	{
		_sound.setBuffer(getSound(sound_index));
		_sprite.setTextureRect(sf::IntRect(518 , 450 , 30 , 13));
		_sprite.setPosition(x , y);
	}
	virtual ~BadGift(){}
	//---------------------------------------------------------
	//Collide bad gift via paddle.
	void collide(const GameObject* gameObjectP , Controller& con)
	{
			Paddle *paddle = (Paddle*) gameObjectP;
			
			if( paddle->getScaleX() > 1.2f )
			{
				paddle->scale( 0.6f , 1);
				_activate = true;
			}
	}
};

