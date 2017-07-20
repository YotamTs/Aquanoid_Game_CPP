#pragma once

#include "Controller.h"

//=-----------------------------------------------------Screen.h-----------------------------------------------------=//
class Screen
{
public:

	Screen(texture_t texture_index)
	{
		_screenPicture.setTexture(getTexture(texture_index));
	}
	//---------------------------------------------------------

	virtual ~Screen(){}
	//---------------------------------------------------------

	virtual void draw(sf::RenderWindow& win)const
	{
		win.draw(_screenPicture);
	}


protected:  //To be draw from inheriting classes
	
	sf::Sprite _screenPicture;


};

