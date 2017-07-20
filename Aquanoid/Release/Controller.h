#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <windows.h>

#include "Board.h"
#include "Paddle.h"
#include "Ball.h"
#include "Gift.h"
#include "BadGift.h"
#include "GiftBigger.h"
#include "GiftFlying.h"

#include "Screen.h"
#include "WelcomeScreen.h"

#include "WinGameScreen.h"
#include "GameOverScreen.h"
#include "HelpScreen.h"

//------------------Enum Section
enum game_state_t
{
	WELCOME , PLAY , HELP , WIN , GAME_OVER , RESTART_LEV
};

enum GIFT_t
{
	BIGGER , SMALLER , LIFE, FLYING, NUM_OF_GIFTS
};

//-------------Const section----------
const std::string FILENAME = "levels.txt";
const std::string TEXT_NEW_LEVEL = "newLevel";
const std::string TEXT_END = "endLevel";

//const for windows exit function.
const TCHAR STRING1[] = TEXT("Do you want to exit the game?");
const TCHAR STRING2[] = TEXT("+--Aquanoid--+");

const int SPACE_FROM_MAX_Y = 50;
const float MENU_X_LOCATION = 700.f;

const int LIFE_AMOUNT = 3;

const sf::Time UPDATE_TIME = sf::seconds(1.f / 30.f);

//=-------------------------------------------------------Controller.h----------------------------------------------------=//
class Controller
{
public:
	Controller(sf::RenderWindow& win);
	~Controller();

	void addGift(float x , float y);
	void removeBrick(int row , int col){_board.setBrickToDestroy(row , col, *this);}
	void oneBrickReduced(){_totalLvBricksRemaining--;}
	void raiseLifeAmount(){_life_amount++;}
	void scoreUpdate(int point){_score += 10;};

private:
	
	//Render window game.
	sf::RenderWindow& _win;
	
	//Level Vecotr.
	std::vector<std::unique_ptr<Level>>_levels;

	//Gifts vector.
	std::vector<std::unique_ptr<Gift>> _giftsVec;

	//Clock & Time Objects:
	sf::Clock _clock;
	sf::Time _elapsedTime;

	//Test:
	sf::Text _numOfScoreText;
	sf::Text _numOfLevText;
	sf::Text _numOfLifeText;
	sf::Text _tryHarderText;

	//Game music:
	sf::Sound _game_music;
	sf::Sound _game_win;
	sf::Sound _game_over;
	sf::Sound _ballDrowing;

	//Enums:
	level_t _currentLv;
	game_state_t _state;

	//Objects:
	Board _board;
	Paddle _paddle;
	Ball _ball;

	//specific for lv members:
	int _totalLvBricksRemaining;

	unsigned int _life_amount = { LIFE_AMOUNT };
	int _score = { 0 };
	
	bool _isPlaying = { false };
	bool _gamePause = { false };
	
	//Backgroung images:
	sf::Sprite _background_lev;
	sf::Sprite _displayMenuSrite;

	//Screen pictures:
	WelcomeScreen _welcomScreen;
	WinGameScreen _winGameScreen;
	GameOverScreen _gameOverScreen;
	HelpScreen _helpSreen;
	
	//------Functions------
	void buildLv(level_t lvToBuild);
	void readFromFile();
	void startGame();
	void playing();
	void moveToNextLevel();
	void drawEverything() const;
	bool exitApplication();
	
};

