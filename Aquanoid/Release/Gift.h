#pragma once

#include "GameObject.h"
#include "Paddle.h"


const float SPEED = 0.4f;
//--------------------------------------------Gift.h---------------------------------------------//

class Gift :
	public GameObject
{
public:
	Gift(sf::RenderWindow& win , sound_t sound_index , texture_t texture_index , float x , float y);
	virtual ~Gift(){}
	
	//---------------------------------------------------------
	sf::Vector2f getPosition() const
	{
		return _sprite.getPosition();
	}
	//---------------------------------------------------------
																		 
	virtual void collide(const GameObject* gameObjectP , Controller& con);
	//---------------------------------------------------------
	virtual void move();

	//---------------------------------------------------------
	virtual void draw() const;



protected:

	sf::Sound _sound;
	bool _giftTaken = { false };
	bool _activate{false};

};

