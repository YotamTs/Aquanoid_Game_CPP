#pragma once

#include "GameObject.h"
#include "Ball.h"
//-------------------------Enum section
enum paddleType_t {STICK_PAD};

//----------------Consts -----------
const int PADDLE_DEFAULT_WIDTH = 100;
const int ANGLE_1 = 95;
const int PRECENT = 100;
const float  PI = 3.14159265358979f;

//=-----------------------------------------------Paddle.h-----------------------------------------------=//
class Paddle : public GameObject												  
{
public:

	Paddle(sf::RenderWindow& win , sound_t sound_index , texture_t texture_index)
		:GameObject(win , texture_index) , _width(PADDLE_DEFAULT_WIDTH)
	{
		_sound.setBuffer(getSound(sound_index));

		//Scale the paddle size:
		_sprite.setScale((float) 2 , (float) 2);	
	}

	virtual ~Paddle(){}

	//------------------------------------------------------------
	void setPosition(int x , int y)
	{
		moveX(x);
		moveY(y);	
	}
	void moveX(int x)
	{
		_sprite.setPosition( (float) x , _sprite.getPosition().y  );		
	}
	void moveY(int y)
	{
		_sprite.setPosition(_sprite.getPosition().x , (float) y);
	}
	
	//------------------------------------------------------------
	const sf::Vector2f& getPosition() const
	{
		return _sprite.getPosition();
	}
	
	//------------------------------------------------------------
	virtual void draw()	const
	{
		_win.draw(_sprite);
	};
	
	void play_sound()
	{
		_sound.play();
	}

	float getScaleX() const
	{
		return  _sprite.getScale().x;		
	}
	//------------------------------------------------------------
	//Check intersection between the ball and the paddle - and direct the ball respectively.
	virtual void collide(const GameObject* gameObjectP , Controller& con)
	{
		Ball *ballP = (Ball*) gameObjectP;

		float offsetX = _sprite.getPosition().x;
		float ballX = ballP->getPosition().x - offsetX;

		float radian = (float) ballX * PI / _width;
		float velocity = ballP->getVelocity();


		if( ballX > _width )//right of paddle
		{
			radian = (float) ( ANGLE_1 * PI ) / PRECENT;
		}
		else if( ballX < 0 )   //left of paddle
		{
			radian = (float) ( 5 * PI ) / PRECENT;
		}
		else
		{
			if( radian < PI / PRECENT )
				radian = (float) ( 5 * PI ) / PRECENT;
			if( radian >(99 * PI) / PRECENT )
				radian = (float) ( ANGLE_1 * PI ) / PRECENT;
		}
		
		ballP->setDirectionX(-velocity * cos(radian));
		ballP->setDirectionY(-velocity * sin(radian));
	}
	//---------------------------------------------------------

	void scale(float x , float y)
	{
		_sprite.scale(x , y);
	}

	void setFlying(bool arg)
	{
		_flying = arg;
	}

	bool isFlying()const
	{
		return _flying;
	}

protected:
	
	sf::Sound _sound;
	int _width;
	bool _flying = { false };

};

