#pragma once

#include "GameObject.h"
#include "Ball.h"

const float BRICK_SCALE = 2.f;

//=-------------------------------------------Brick.h----------------------------------------=//

class Brick : public GameObject
{
public:

	Brick(sf::RenderWindow& win , sound_t sound_index , texture_t texture_index, std::pair<int,int> pos)
		:GameObject(win , texture_index) , _pos(pos)
	{
		_sound.setBuffer(getSound(sound_index));
	}
	virtual ~Brick(){}
	
	//---------------------------------------------------------
	virtual void draw() const;
	//---------------------------------------------------------	
	virtual void play_sound();
	
	//---------------------------------------------------------
	//Default implimitation for regular brick.
	virtual void collide(const GameObject* gameObjectP , Controller& con);
	
	//---------------------------------------------------------
	//Update ball direction:
	virtual void ballUpdate(Ball *ballP);
	
	//---------------------------------------------------------
	virtual void destroy(Controller& con);
		
	//-----------------Getters & Setters-----------------------
	void setSprite(const sf::IntRect& spritePosition)
	{
		_sprite.setTextureRect(spritePosition);
	}
	
	void setSpritePosition(int xPixel , int yPixel , int offsetX = 0 , int offsetY = 0)
	{
		_sprite.setPosition((float) xPixel + (float) offsetX , (float) yPixel + (float) offsetY);
	}
	
	float getLeft() const
	{
		return _sprite.getPosition().x;	
	}
	float getRight() const
	{
		return _sprite.getPosition().x + _sprite.getGlobalBounds().width;
	}
	float getTop() const
	{
		return _sprite.getPosition().y ;
	}
	float getBottom() const
	{
		return _sprite.getPosition().y + _sprite.getGlobalBounds().height;
	}
	const bool& isDestroyed() const
	{
		return _destroyed;
	}

protected:
	sf::Sound _sound;
	bool _destroyed = false;
	std::pair<int , int> _pos;

};

