#include "Gift.h"
#include "Controller.h"

//------------------------------------------------------Gift.cpp------------------------------------------------------//


Gift::Gift(sf::RenderWindow& win , sound_t sound_index , texture_t texture_index , float x , float y)
	:GameObject(win , texture_index)
{
	_sound.setBuffer(getSound(sound_index));
	_sprite.setTextureRect(sf::IntRect(337 , 446 , 42 , 19));
	_sprite.setPosition(x , y);
}
//---------------------------------------------------------
//Collide gift via paddle.
void Gift::collide(const GameObject* gameObjectP , Controller& con)
{
	if( !_activate )
	{
		con.raiseLifeAmount();
		_activate = true;
	}
}
//---------------------------------------------------------
//Move gift, create a "realistic" falling down from the brick.
void Gift::move()
{
	auto new_speed = _sprite.getPosition();
	new_speed.y += SPEED;
	_sprite.setPosition(new_speed);
};
//---------------------------------------------------------
//Drawing func:
void Gift::draw() const
{
	if( !_giftTaken )
	{
		_win.draw(_sprite);
	}
};