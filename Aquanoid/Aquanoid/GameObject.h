#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Level.h"

class Controller;
//=-------------------------------------------GameObject.h----------------------------------------=//
class GameObject
{
public:

	GameObject(sf::RenderWindow& win , texture_t texture_index) :_win(win)
	{
		_sprite.setTexture(getTexture(texture_index));
	}
	virtual ~GameObject(){}

	//-------Pure virtual functions-------//
	virtual void draw() const = 0;
	virtual void collide(const GameObject* gameObjectP , Controller& con) = 0;
	
	//Check if collide with recived gameObjet:
	virtual bool isCollide(const GameObject& gameObject) const
	{
		return _sprite.getGlobalBounds().intersects(gameObject._sprite.getGlobalBounds());
	}


protected:

	sf::RenderWindow& _win;
	sf::Sprite _sprite;

};

