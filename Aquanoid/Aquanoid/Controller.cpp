#include "Controller.h"

//=-------------------------------------------Controller.cpp----------------------------------------=//

//--------------------------------Constructor
Controller::Controller(sf::RenderWindow& win)
	:_win(win) , _state(WELCOME) , _paddle(win , BOING , PADDLE_TEXTURE) , _ball(win , BALL_TEXTURE)
{
	//Starting from level one.
	_currentLv = LEVEL_ONE;

	//set menu location:
	_displayMenuSrite.setTexture(getTexture(DISPLAYMENU_TEX));
	_displayMenuSrite.setPosition(MENU_X_LOCATION , 0);

	//Read data from file & create Level vector from the file.
	readFromFile();

	//Set game music:
	_game_music.setBuffer(getSound(MUSIC));
	_game_music.setVolume(50);
	_game_win.setBuffer(getSound(WIN_SOUND));
	_game_over.setBuffer(getSound(GAME_OVER_SOUND));
	_ballDrowing.setBuffer(getSound(DROWING));

	//Set Text:
	_tryHarderText = createText("Try Harder!" , sf::Color::Green , 60 , 250 , 300 , false);

	//Clock restart:
	_clock.restart();
	_elapsedTime = _clock.restart();
	
	//Start the game:
    startGame();
}
//------------------------------------------------------------------------
Controller::~Controller(){}
//------------------------------------------------------------------------
/*
* Start the game function.
*/
void Controller::startGame()
{
	//----------------------Window----------------------//
	while( _win.isOpen() )
	{
		auto windowSize = _win.getSize();
		sf::Event Event;

		while( _win.pollEvent(Event) )
		{
			switch( Event.type )
			{
				case sf::Event::Closed:

					_win.close();
					break;
					//----------------------KeyPressed Event----------------------//
				case sf::Event::KeyPressed:

					if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) )
					{
						if( exitApplication() )
						{
							exit(EXIT_SUCCESS);
						}
					}
					//Pause the game and see the Help screen.
					else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) )
					{
						if( _state == HELP && !_isPlaying ) //Help screen while not playing.
						{
							_state = WELCOME;
						}
						else if (_state == HELP && _isPlaying) //Help screen while playing.
						{
							_gamePause = false;
							_state = PLAY;	
						}						
						//Pause game on or off:
						else if( !_gamePause && _state == PLAY)
						{
							_gamePause = true;
							_state = HELP;													
						}
					}
					break;
					//----------------------MouseButtonPressed Event----------------------//
				case sf::Event::MouseButtonPressed:

					if( _state == WELCOME)//Checking if it welcom screen. 
					{
						if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
						{
							if( _welcomScreen.isStartBtnClicked((float) Event.mouseButton.x ,
								(float) Event.mouseButton.y) )
							{
								_isPlaying = true;
								_life_amount = LIFE_AMOUNT;
								_game_music.play();
								_game_music.setLoop(true);
								_paddle.setFlying(false);
								buildLv(LEVEL_ONE);
								_state = PLAY;
			

								
								//If the paddle was reszie from a gift - return it to the original size.
								if( _paddle.getScaleX() < 1 )
								{
									_paddle.scale(4 , 1);
								}
								else if( _paddle.getScaleX() > 3 )
								{
									_paddle.scale(0.5 , 1);
								}
							}
							if( _welcomScreen.isHelpBtnClicked((float) Event.mouseButton.x ,
								(float) Event.mouseButton.y) )
							{
								_state = HELP;				
							}
						}
					}
					else if( _state == RESTART_LEV )
					{
						if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
						{
							_state = PLAY;
						}
					}
					else if( _state == GAME_OVER || _currentLv == NUM_OF_LEVELS )
					{
						if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
						{
							_state = WELCOME;							
						}
					}
					break;
					//----------------------MouseMoved Event----------------------//
				case sf::Event::MouseMoved:

					if( _state == PLAY)
					{
					if( sf::Mouse::getPosition(_win).x < (float) windowSize.x - 300 ) 					
						{
							//set Cursor invisible:
							_win.setMouseCursorVisible(false);
													
							if( _paddle.isFlying() )
							{
								//Flying Paddle
								_paddle.moveY(sf::Mouse::getPosition(_win).y + 90);
							}							
							//Checking again that paddle not outside the borders while taking gifts:
							if( _paddle.getScaleX() < 1.5)
							{
								_paddle.moveX(sf::Mouse::getPosition(_win).x + 90);
							}
							else if( _paddle.getScaleX() > 3)
							{
								_paddle.moveX(sf::Mouse::getPosition(_win).x - 75);
							}
							else
							{
								_paddle.moveX(sf::Mouse::getPosition(_win).x );
							}
						}
					}			
					break;
			}//End Event.type 
		}//end while pollEvent	  

		//------------Update elapsedTime--------------//
		_elapsedTime += _clock.restart();

		//------------------------Checking area------------------------------//	

		//Test for Win or Loose:
		if( _isPlaying && _state == PLAY   && (_totalLvBricksRemaining == 0) )
		{
			moveToNextLevel();					
		}
		//If loose:
		else if( _isPlaying && _state == PLAY && (_ball.getPosition().y > 785) )
		{
			_life_amount--;

			if( _life_amount == 0 )	//loose the game.
			{
				_state = GAME_OVER;
				_game_music.stop();
				_game_over.play();
			}
			else
			{
				_ballDrowing.play();
				_state = RESTART_LEV;
			}
		}
//---------------------------------------------------------
		//isPlayinf func:
		if( _isPlaying && !_gamePause )
		{
			playing();
			_numOfLevText = createText(std::to_string((int)_currentLv + 1) , sf::Color::Black , 30 , 790 , 110 , false);
			_numOfLifeText = createText(std::to_string(_life_amount) , sf::Color::Black , 30 , 795 , 320 , false);
			_numOfScoreText = createText(std::to_string(_score) , sf::Color::Black , 30 , 780 , 510 , true);

			switch( _currentLv )
			{
				//draw background image according to level number:
				case LEVEL_ONE:
					_background_lev.setTexture(getTexture(BACKGROUND_1_TEX));
					break;
				case LEVEL_TWO:
					_background_lev.setTexture(getTexture(BACKGROUND_2_TEX));
					break;
				case LEVEL_THREE:
					_background_lev.setTexture(getTexture(BACKGROUND_3_TEX));
					break;
				default:
					break;
			}
		}
		//---------------------------------------------------------------
		//Iterate Bricks2D, check for collision & perform collide action:
		if( !_gamePause )
		{
			for( auto& it : _board.getBricks2D() )
			{
				if( it.second->isCollide(_ball) )
				{
					it.second->collide(&_ball , *this);
				}
			}
		}
		//---------------------------------------------------------------
		// Ball & Paddle collision:
		if( (_paddle.isCollide(_ball) && _state == PLAY) && !_gamePause  )
		{
			_paddle.collide(&_ball , *this);
			_paddle.play_sound();
		}

		//---------------------------------------------------------------
		//Iterate in game gifts , updates position, check for collision & perform collide action:
		if( !_gamePause )
		{
			bool test = true;
			for( auto& it : _giftsVec )
			{
				it->move();
				if( it->getPosition().y < _win.getSize().y )
				{
					test = false;
				}
				if( it->isCollide(_paddle) )
				{
					it->collide(&_paddle , *this);	
				}
			}
			if( test )
			{
				if( _giftsVec.size() > 0 )
					_giftsVec.clear();
			}
		}
		//-----------------------------------------------------------
		//Update board by earsing the wanted bricks:
		if( !_gamePause )
		{
			_board.updateBoard();
		}
		//----------------------Draw Section----------------------//
		drawEverything();

		_win.display();

	}//End window.isOpen
}
//-------------------------------------------------------------------------------
/*
* builds the level (given by arguments) according to Level in vector.
*/
void Controller::buildLv(level_t currentLv)
{
	auto windowSize = _win.getSize();

	//1) set current game values (current lv, time left, max moves- the controller 3 privates)
	_currentLv = currentLv;

	//2) create bricks:
	_totalLvBricksRemaining = _board.buildBoard(*_levels[currentLv] , _win);

	//Set paddle & ball positions::
	_paddle.setPosition(windowSize.x / 2 , windowSize.y - SPACE_FROM_MAX_Y);

	//_ball.setPosition(windowSize.x/2 , windowSize.y - 400 );
}
//-----------------------------------------------------------------------------------	  
/*
*Draw Everything function.
*/
void Controller::drawEverything() const
{
	if( _state == WELCOME )
	{
		_win.clear();
		_welcomScreen.draw(_win);
	}
	//Draw win_game screen.
	else if( _currentLv == NUM_OF_LEVELS )
	{
		_win.clear();
		_winGameScreen.draw(_win);
		_win.setMouseCursorVisible(true);
	}
	else if( _state == GAME_OVER )
	{
		_win.clear();
		_gameOverScreen.draw(_win);
		_win.setMouseCursorVisible(true);		
	}
	else if( _state == RESTART_LEV )
	{
		_win.clear();
		_win.setMouseCursorVisible(true);
		_win.draw(_tryHarderText);
	}
	else if( _state == HELP )
	{
		_helpSreen.draw(_win);
		_win.setMouseCursorVisible(true);
	}
	else  //playing time:
	{
		_win.clear();

		if( _isPlaying && _state == PLAY )
		{
			//Draw background level:
			_win.draw(_background_lev);

			//Draw bricks:
			_board.draw(_win);

			//Draw gifts:
			for( auto& it : _giftsVec )
				it->draw();

			//Draw menu:  
			_win.draw(_displayMenuSrite);

			//Draw ball/s and paddle
			_paddle.draw();
			_ball.draw();

			//Draw text:
			_win.draw(_numOfScoreText);
			_win.draw(_numOfLevText);
			_win.draw(_numOfLifeText);
		}
	}
}
//-------------------------------------------------------------------------------
//Adding gift (when hit the gift brick - this func called from GiftBrick class).
void Controller::addGift(float x , float y)
{
	/* generate random number between enum members: */
	int gift = rand() % (int) NUM_OF_GIFTS;
	 
	switch( (GIFT_t) gift )
	{
		case LIFE:
			_giftsVec.emplace_back(std::unique_ptr<Gift>(new Gift(_win , BOING , BRICKS_TEXTURE , x , y)));
			break;
		case SMALLER:
			_giftsVec.emplace_back(std::unique_ptr<Gift>(new BadGift(_win , BOING , BRICKS_TEXTURE , x , y)));
			break;
		case BIGGER:
				_giftsVec.emplace_back(std::unique_ptr<Gift>(new GiftBigger(_win , BOING , BRICKS_TEXTURE , x , y)));
				break;
		case FLYING:
			_giftsVec.emplace_back(std::unique_ptr<Gift>(new GiftFlying(_win , BOING , BRICKS_TEXTURE , x , y)));
		default:
			break;
	}
}
//-------------------------------------------------------------------------------
void Controller::playing()
{
	while( _elapsedTime >= UPDATE_TIME )
	{
		//Auto :)
		auto delta = UPDATE_TIME.asSeconds() * _ball.getVelocity();
		auto direction = _ball.getDirection();
		auto position = _ball.getPosition();
		auto radius = _ball.getRadius();
		auto windowSize = _win.getSize();


		sf::Vector2f new_pos(position.x + direction.x * delta , position.y + direction.y * delta);

		if( new_pos.x - radius < 0 )
		{	//left window edge	 
			_ball.setDirectionX(direction.x * ( -1 ));
			new_pos.x = 0 + radius;
		}
		else if( new_pos.x + radius >= windowSize.x - 200 )
		{	//right window edge
			_ball.setDirectionX(direction.x * ( -1 ));
			new_pos.x = windowSize.x - 200 - radius;
		}
		else if( new_pos.y - radius < 0 )
		{	//top of window
			_ball.setDirectionY(direction.y * ( -1 ));
			new_pos.y = 0 + radius;
		}
		else if( new_pos.y + radius >= windowSize.y )
		{	//bottom of window
			_ball.setDirectionY(direction.y * ( -1 ));
			new_pos.y = windowSize.y - radius;
		}

		//Update position:
		_ball.setPosition(new_pos.x , new_pos.y);

		//Timing:
		_elapsedTime -= UPDATE_TIME;
	}//end isPlaying	
}
//-------------------------------------------------------------------------------
//Moving to the next level or finish game.
void Controller::moveToNextLevel()
{
	_currentLv = (level_t) ( ( _currentLv + 1 ) );

	if( _currentLv == NUM_OF_LEVELS )
	{
		_game_music.stop();
		//Play win sound
		_game_win.play();
		
		_isPlaying = false;
		_life_amount = LIFE_AMOUNT;
	}
	else //finish a level
	{
		buildLv(_currentLv);
	}
}
//-----------------------------------------------------------------------------------
/*
*  Read from file function:
*/
void Controller::readFromFile()
{
	std::ifstream infile;
	std::stringstream ss;
	std::string line , word;

	int lv_counter = -1 , lineCounter = -1;

	infile.open(FILENAME);
	try
	{
		if( !infile.is_open() )
		{
			throw MyException("Cannot load" + FILENAME , 493);
		}
	}
	catch( MyException &exp )
	{
		exp.show();
		exit(EXIT_FAILURE);
	}

	//Read lines until end of file.
	while( !infile.eof() )
	{
		word.clear();

		//read a single line
		getline(infile , line);

		//put line into string stream:
		ss.str(line);

		//read first word from string:
		ss >> word;

		if( word.compare(TEXT_NEW_LEVEL) == 0 )
		{
			_levels.push_back(std::unique_ptr<Level>(new Level()));

			ss.clear();

			lv_counter++;
			lineCounter = -1;

			word.clear();
			continue;
		}

		if( word.compare(TEXT_END) == 0 )
		{
			ss.clear();
			continue;
		}

		//Read character in each line, and insert it to _levels vector at level counter place.
		lineCounter++;
		for( size_t i = 0; i < line.length(); i++ )
		{
			_levels[lv_counter]->addRow();
			switch( line[i] )
			{
				case 'B':
					_levels[lv_counter]->addChar(lineCounter , 'B');
					break;
				case 'U':
					_levels[lv_counter]->addChar(lineCounter , 'U');
					break;
				case 'G':
					_levels[lv_counter]->addChar(lineCounter , 'G');
					break;
				case 'X':
					_levels[lv_counter]->addChar(lineCounter , 'X');
					break;
				default:
					_levels[lv_counter]->addChar(lineCounter , '.');
					break;
			}
		}
		//cleaning stream for next line:
		ss.clear();
	}//while not eof
	infile.close();
}
//-------------------------------------------------------------------------------
/*
*Show window box for cancelling the game.
*/
bool Controller::exitApplication()
{
	int result;
	result = MessageBox(NULL , STRING1 , STRING2 , MB_OKCANCEL);

	if( result == IDOK )
	{
		return true;
	}
	return false;
}

