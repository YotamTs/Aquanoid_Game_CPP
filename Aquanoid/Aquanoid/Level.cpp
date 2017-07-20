#include "Level.h"

//=-------------------------------------------Level.cpp----------------------------------------=//
//----------
/*
* GetTexture
*/
sf::Texture& getTexture(texture_t texture)
{
	static bool first_time = true ;

	//Paddle textures:
	static sf::Texture brickTexture;
	static sf::Texture paddleTexture;
	static sf::Texture ballTexture;

	//Backgrounds textures:
	static sf::Texture backgroundTextures1;
	static sf::Texture backgroundTextures2;	
	static sf::Texture backgroundTextures3;	

	static sf::Texture displayMenuTexture;

	//Screens textures:
	static sf::Texture welcomeScreenTexture;
	static sf::Texture helpScreenTexture;		
	static sf::Texture winGameScreenTexture;	
	static sf::Texture GameOverScreenTexture;

		if( first_time )
		{
			first_time = false;
			try
			{
				//Objects textures:
				if( !brickTexture.loadFromFile(BRICKS_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + BRICKS_TEXTURE_PATH , 37);
				}
				if( !paddleTexture.loadFromFile(PADDLE_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + PADDLE_TEXTURE_PATH , 41);
				}
				if( !ballTexture.loadFromFile(BALL_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + BALL_TEXTURE_PATH , 45);
				}

				//Background textures:
				if( !backgroundTextures1.loadFromFile(BACKGROUND_1_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + BACKGROUND_1_TEXTURE_PATH , 51);
				}
				if( !backgroundTextures2.loadFromFile(BACKGROUND_2_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + BACKGROUND_2_TEXTURE_PATH , 56);
				}
				if( !backgroundTextures3.loadFromFile(BACKGROUND_3_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + BACKGROUND_3_TEXTURE_PATH , 61);
				}
				if( !displayMenuTexture.loadFromFile(DISPLAY_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + DISPLAY_TEXTURE_PATH , 66);
				}

				//Screens pictures textures:
				if( !welcomeScreenTexture.loadFromFile(WELCOME_PIC_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + WELCOME_PIC_TEXTURE_PATH , 74);
				}
				if( !helpScreenTexture.loadFromFile(HELP_PIC_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + HELP_PIC_TEXTURE_PATH , 79);
				}
				if( !winGameScreenTexture.loadFromFile(WIN_PIC_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + WIN_PIC_TEXTURE_PATH , 84);
				}
				if( !GameOverScreenTexture.loadFromFile(GAME_OVER_PIC_TEXTURE_PATH) )
				{
					throw MyException("Cannot load" + GAME_OVER_PIC_TEXTURE_PATH , 89);
				}
			}
			catch( MyException &exp )
			{
				exp.show();
				exit(EXIT_FAILURE);
			}
	}
	//Switch texture enum and return it texture:
	switch( texture )
	{
		case BRICKS_TEXTURE:
			return brickTexture;
			break;
		case PADDLE_TEXTURE:
			return paddleTexture;
			break;
		case BALL_TEXTURE:
			return ballTexture;
			break;

		case BACKGROUND_1_TEX:
			return backgroundTextures1;
			break;
		case BACKGROUND_2_TEX:
			return backgroundTextures2;
			break;
		case BACKGROUND_3_TEX:
			return backgroundTextures3;
			break;

		case DISPLAYMENU_TEX:
			return displayMenuTexture;
			break;
		case WELCOME_PIC:
			return welcomeScreenTexture;
			break;
		case HELP_PIC:
			return helpScreenTexture;
			break;
		case WIN_GAME_PIC:
			return winGameScreenTexture;
			break;
		case GAME_OVER_PIC:
			return GameOverScreenTexture;
			break;
	}
	return paddleTexture;
}
//--------
/*
* GetSound
*/
sf::SoundBuffer& getSound(sound_t sound)
{
	static bool first_time = true ;

	//Sounds Buffers
	static sf::SoundBuffer musicBuff;
	static sf::SoundBuffer gameWinBuff;
	static sf::SoundBuffer gameOverBuff;
		
	static sf::SoundBuffer boingBuff;
	static sf::SoundBuffer brickBuff;
	static sf::SoundBuffer magicBuff;
	static sf::SoundBuffer explodeBuff;
	static sf::SoundBuffer ballDrowingBuff;

	if( first_time )
	{
		first_time = false;
		try
		{
			if( !musicBuff.loadFromFile(MUSIC_SOUND_PATH) )
			{
				throw MyException("Cannot load" + MUSIC_SOUND_PATH , 162);
			}
			if( !gameWinBuff.loadFromFile(WIN_SOUND_PATH) )
			{
				throw MyException("Cannot load" + WIN_SOUND_PATH , 166);
			}
			if( !gameOverBuff.loadFromFile(GAME_OVER_SOUND_PATH) )
			{
				throw MyException("Cannot load" + GAME_OVER_SOUND_PATH , 170);
			}
			if( !ballDrowingBuff.loadFromFile(DROWING_SOUND_PATH) )
			{
				throw MyException("Cannot load" + DROWING_SOUND_PATH , 174);
			}
			if( !boingBuff.loadFromFile(BOING_SOUND_PATH) )
			{
				throw MyException("Cannot load" + BOING_SOUND_PATH , 178);
			}
			if( !brickBuff.loadFromFile(BRICK_SOUND_PATH) )
			{
				throw MyException("Cannot load" + BRICK_SOUND_PATH , 182);
			}
			if( !magicBuff.loadFromFile(MAGIC_SOUND_PATH) )
			{
				throw MyException("Cannot load" + MAGIC_SOUND_PATH , 186);
			}
			if( !explodeBuff.loadFromFile(EXPLODE_SOUND_PATH) )
			{
				throw MyException("Cannot load" + EXPLODE_SOUND_PATH , 190);
			}
		}
		catch( MyException &exp )
		{
			exp.show();
			exit(EXIT_FAILURE);
		}
	}
	//Switch sound enum and return it sound:
	switch( sound )
	{
		case MUSIC:
			return musicBuff;
			break;
		case GAME_OVER_SOUND:
			return gameOverBuff;
			break;
		case WIN_SOUND:
			return gameWinBuff;
			break;
		case BOING:
			return boingBuff;
			break;
		case DROWING:
			return ballDrowingBuff;
			break;
		case BRICK:
			return brickBuff;
			break;	
		case MAGIC:
			return magicBuff;
			break;
		case EXPLODE:
			return explodeBuff;
			break;
	}
	return boingBuff;
}
//--------
/*
* Get Text:
*/
sf::Text createText(std::string str , sf::Color color , int fontSize , int xPos , int yPos , bool isUnderLine)
{
		static bool first_time = true ;
		static sf::Font font;

		if( first_time )
		{
			try
			{
				first_time = false;
				if( !font.loadFromFile(FONT_TEXT_PATH) )
				{
					throw MyException("Cannot load" + FONT_TEXT_PATH , 248);
				}
			}
			catch( MyException &exp )
			{
				exp.show();
				exit(EXIT_FAILURE);
			}
		}

	sf::Text textToReturn(str , font , fontSize);
	textToReturn.setColor(color);
	if( isUnderLine )
	{
		textToReturn.setStyle(sf::Text::Underlined);
	}
	
	textToReturn.setPosition((float) xPos , (float) yPos);

	return 	textToReturn;
}