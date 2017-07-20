#include "Board.h"

#include "UnbreakableBrick.h"
#include "GiftBrick.h"
#include "ExplodingBrick.h"


//=-------------------------------------------Board.cpp----------------------------------------=//

int Board::buildBoard(const Level& level , sf::RenderWindow& win)
{
	int bricksCounter = 0;
	//Insert the wanted objects to the board game:
	auto bricksChar2d = level.getCharBoard2d();

	for( size_t i = 0; i < bricksChar2d.size(); i++ )
	{		
		for( size_t j = 0; j < bricksChar2d[i].size(); j++ )
		{
			switch( bricksChar2d[i][j] )
			{
				case 'B':			
					_bricks2D[std::make_pair(i , j)] = std::unique_ptr<Brick>(new Brick(win , BRICK , BRICKS_TEXTURE , std::make_pair(i , j)));
					_bricks2D[std::make_pair(i , j)]->setSprite(sf::IntRect(320 , 272 , BRICK_WIDTH , BRICK_HEIGHT));
					_bricks2D[std::make_pair(i , j)]->setSpritePosition(j * BRICK_WIDTH , i * BRICK_HEIGHT , j* WIDTH_OFFSET , i * HEIGHT_OFFSET);
					bricksCounter++;
					break;
				case 'U':
					_bricks2D[std::make_pair(i , j)] = std::unique_ptr<Brick>(new UnbreakableBrick(win , BRICK , BRICKS_TEXTURE , std::make_pair(i , j)));
					_bricks2D[std::make_pair(i , j)]->setSprite(sf::IntRect(512 , 544 , BRICK_WIDTH , BRICK_HEIGHT));
					_bricks2D[std::make_pair(i , j)]->setSpritePosition(j * BRICK_WIDTH , i * BRICK_HEIGHT , j* WIDTH_OFFSET , i * HEIGHT_OFFSET);
					break;
				case 'G':
					_bricks2D[std::make_pair(i , j)] = std::unique_ptr<Brick>(new GiftBrick(win , MAGIC , BRICKS_TEXTURE , std::make_pair(i , j)));
					_bricks2D[std::make_pair(i , j)]->setSprite(sf::IntRect(160 , 400 , BRICK_WIDTH , BRICK_HEIGHT));
					_bricks2D[std::make_pair(i , j)]->setSpritePosition(j * BRICK_WIDTH , i * BRICK_HEIGHT , j* WIDTH_OFFSET , i * HEIGHT_OFFSET);
					bricksCounter++;
					break;
				case 'X':
					_bricks2D[std::make_pair(i , j)] = std::unique_ptr<Brick>(new ExplodingBrick(win , EXPLODE , BRICKS_TEXTURE , std::make_pair(i , j)));
					_bricks2D[std::make_pair(i , j)]->setSprite(sf::IntRect(0 , 448 , BRICK_WIDTH , BRICK_HEIGHT));
					_bricks2D[std::make_pair(i , j)]->setSpritePosition(j * BRICK_WIDTH , i * BRICK_HEIGHT , j* WIDTH_OFFSET , i * HEIGHT_OFFSET);
					bricksCounter++;
					break;
				default:
					break;
			}
		}
	}
	return bricksCounter;
}
