#pragma once

#include "GameObject.h"

//Ball enum type:
enum ballType_t {NORMAL_BALL, FAST_BALL, SLOW_BALL, DUPLICATE_BALL};

//-------------------Const section-------------------//
const float SCALE_SIZE = .8f;
const sf::Vector2f VELOCITY(-22 , -12);

//=-------------------------------------------------------Ball.h---------------------------------------------------=//
class Ball : public GameObject
{

public:
	
	Ball(sf::RenderWindow& win , texture_t texture_index)
		:GameObject(win , texture_index)
	{
		_sprite.setScale(SCALE_SIZE , SCALE_SIZE);
		_radius = _sprite.getGlobalBounds().height / 2;
		_sprite.setOrigin(_radius , _radius);
	
		_direction = VELOCITY;
		//set velocity:		
		_velocity = std::sqrt(_direction.x * _direction.x + _direction.y * _direction.y);
	}
	virtual ~Ball() {}

	//------------------------------------------------------------
	virtual void draw() const
	{
		_win.draw(_sprite);
	};
	//------------------------------------------------------------
	virtual void collide(const GameObject* gameObjectP , Controller& con){}

	//-------------------------Getters & Setters---------------------------
	sf::Vector2f getPosition()
	{
		return _sprite.getPosition();
	}
	void setPosition(float x, float y)
	{
		_sprite.setPosition(x , y);
	}

	const float& getVelocity() const
	{
		return _velocity;
	}
	void setVelocity(float velocity)
	{
		_velocity = velocity;
	}
	
	const float& getRadius() const
	{
		return _radius;
	}
	
	const sf::Vector2f& getDirection() const
	{
		return _direction;
	}
	void setDirectionX(float directionX)
	{
		_direction.x = directionX;
	}
	void setDirectionY(float directionY)
	{
		_direction.y = directionY;
	}

	float getLeft() const
	{
		return _sprite.getPosition().x - _radius;
	}

	float getRight() const
	{
		return _sprite.getPosition().x + _radius;
	}

	float getTop() const
	{
		return _sprite.getPosition().y - _radius;
	}

	float getBottom() const
	{
		return _sprite.getPosition().y + _radius;
	}


private:

	float _velocity;

	float _radius;

	sf::Vector2f _direction;
};

