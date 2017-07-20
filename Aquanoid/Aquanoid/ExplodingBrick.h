#pragma once

#include "Brick.h"
#include "Controller.h"

//=-------------------------------------------ExplodingBrick.h----------------------------------------=//
class ExplodingBrick : public Brick
{
public:

	ExplodingBrick(sf::RenderWindow& win , sound_t sound , texture_t texture , std::pair<int , int> pos)
		:Brick(win , sound , texture, pos){}

	virtual ~ExplodingBrick(){}

	//---------------------------------------------------------

	virtual void collide(const GameObject* gameObjectP , Controller& con)
	{
		_destroyed = true;

		Ball *ballP = (Ball*) gameObjectP;
		ballUpdate(ballP);

		for( int i = _pos.first - 1; i <= _pos.first + 1; i++ )
		{
			for( int j = _pos.second - 1; j <= _pos.second + 1; j++ )
			{
				con.removeBrick(i , j);
				con.scoreUpdate(20);
			}
		}
	}

	//---------------------------------------------------------

	virtual void destroy(Controller& con)
	{
		if( !_destroyed )
		{
			_destroyed = true;

			for( int i = _pos.first - 1; i <= _pos.first + 1; i++ )
			{
				for( int j = _pos.second - 1; j <= _pos.second + 1; j++ )
				{
					con.removeBrick(i , j);
				}
			}
		}			
	}


};

