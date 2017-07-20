#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "MyException.h"

//-----------------------Enum Section---------------------------	   
enum texture_t
{
	BRICKS_TEXTURE , 
	PADDLE_TEXTURE , 
	BALL_TEXTURE ,
	DISPLAYMENU_TEX ,
	BACKGROUND_1_TEX,
	BACKGROUND_2_TEX,
	BACKGROUND_3_TEX,
	WELCOME_PIC,
	HELP_PIC,
	WIN_GAME_PIC,
	GAME_OVER_PIC
};

enum level_t {LEVEL_ONE , LEVEL_TWO , LEVEL_THREE , NUM_OF_LEVELS};

enum sound_t{MUSIC, WIN_SOUND, GAME_OVER_SOUND, DROWING,  BRICK , EXPLODE, BOING ,  MAGIC};

//----------------Const string for loadind textures-----------
const std::string BRICKS_TEXTURE_PATH = "utilites/bricks.png";
const std::string PADDLE_TEXTURE_PATH = "utilites/paddle.png";
const std::string BALL_TEXTURE_PATH = "utilites/ball.png";
const std::string DISPLAY_TEXTURE_PATH = "utilites/dispalyMenu.png";


const std::string BACKGROUND_1_TEXTURE_PATH = "utilites/background1.png";
const std::string BACKGROUND_2_TEXTURE_PATH = "utilites/background2.png";
const std::string BACKGROUND_3_TEXTURE_PATH = "utilites/background3.png";


const std::string WELCOME_PIC_TEXTURE_PATH = "utilites/welcome.png";
const std::string HELP_PIC_TEXTURE_PATH = "utilites/help.png";
const std::string WIN_PIC_TEXTURE_PATH = "utilites/gamewin.png";
const std::string GAME_OVER_PIC_TEXTURE_PATH = "utilites/gameOver.png";

//----------------Const string for loadind sounds-------------
const std::string BRICK_SOUND_PATH = "utilites/brick.ogg";
const std::string MAGIC_SOUND_PATH = "utilites/magic.ogg";
const std::string EXPLODE_SOUND_PATH = "utilites/explode.ogg";

const std::string BOING_SOUND_PATH = "utilites/boing.ogg";
const std::string MUSIC_SOUND_PATH = "utilites/music.ogg";
const std::string WIN_SOUND_PATH = "utilites/win.ogg";
const std::string GAME_OVER_SOUND_PATH = "utilites/gameOver.ogg";
const std::string DROWING_SOUND_PATH = "utilites/ballDrowning.ogg";

//---------------------------Font-----------------------------
const std::string FONT_TEXT_PATH = "utilites/font.ttf";

//=-----------------------------------------------------Level.h-----------------------------------------------------=//
class Level
{
public:

	void addChar(int row, char symbol)
	{
		_charBoard2d[row].push_back(symbol);
	}
	//----------------------------------------------
	void addRow()
	{
		_charBoard2d.push_back(std::vector<char>());
	}
	//----------------------------------------------
	std::vector<std::vector<char>> getCharBoard2d() const
	{
		return _charBoard2d;
	}
	//----------------------------------------------
private:
	
	std::vector<std::vector <char>> _charBoard2d;
};


//------------------Get texture & sound functions---------------------
sf::Texture& getTexture(texture_t texture);
sf::SoundBuffer& getSound(sound_t sound);
sf::Text createText(std::string str , sf::Color color , int fontSize , int xPos , int yPos , bool isUnderLine);
