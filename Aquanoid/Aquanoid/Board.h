#pragma once

#include "GameObject.h"
#include "Brick.h"

//----------Const Section-----------//
const int BRICK_WIDTH = 32;
const int BRICK_HEIGHT = 16;

const int WIDTH_OFFSET = 2;
const int HEIGHT_OFFSET = 2;

//=-----------------------------------------------Board.h------------------------------------------------=//
class Board
{
public:

	//Building the board.
	int buildBoard(const Level& level , sf::RenderWindow& win);

	//--------------------------------------------------------------
	//Run on map bricks and draw each brick.
	void draw(sf::RenderWindow& win) const
	{
		for( auto& it : _bricks2D )
		{	
			//draw brick
			it.second->draw();
		}
	}
	//--------------------------------------------------------------
	//Get function - Return the _bricks2D:
	const std::map<std::pair<int , int> , std::unique_ptr<Brick>>& getBricks2D() const
	{
		return _bricks2D;
	}
	
	//--------------------------------------------------------------
	//function check in _bricks2D if any brick has been destroyed, if so - erase it.
	void updateBoard()
	{
		for( auto it = _bricks2D.begin() , ite = _bricks2D.end(); it != ite; )
		{
			if( it->second->isDestroyed() )
				it = _bricks2D.erase(it);
			else
				++it;
		}
	}
	
	//--------------------------------------------------------------	
	void setBrickToDestroy(int row , int col , Controller& con)
	{
		//check if brick exist:
		auto it = _bricks2D.find(std::make_pair(row , col));
		
		if( it == _bricks2D.end() )
		{
			//Brick not found
		}
		else //found
		{			
			it->second->destroy(con); //Destroy brick
		}
	}

private:

	//Map that has a brick object and it location:
	std::map<std::pair<int , int> , std::unique_ptr<Brick>> _bricks2D;
};

