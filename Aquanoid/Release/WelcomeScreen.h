#pragma once
#include "Screen.h"

//-----------------Const section
const float BTN_START_X1 = 112.f;
const float BTN_START_X2 = 782.f;
const float	BTN_START_Y1 = 717.f;
const float	BTN_START_Y2 = 750.f;

const float	BTN_EXIT_X1 = 286.f;
const float	BTN_EXIT_X2 = 606.f;
const float	BTN_EXIT_Y1 = 595.f;
const float	BTN_EXIT_Y2 = 631.f;


//----------------------------------------WelcomeScreen.h------------------------------------//
class WelcomeScreen : public Screen
{
public:

	WelcomeScreen() :Screen(WELCOME_PIC){}

	virtual ~WelcomeScreen() {}
	//---------------------------------------------------------

	bool isStartBtnClicked(float x , float y)
	{
		return( x > BTN_START_X1 && x < BTN_START_X2 && y > BTN_START_Y1 && y < BTN_START_Y2 );
	}
	//---------------------------------------------------------

	bool isHelpBtnClicked(float x , float y)
	{
		return( x > BTN_EXIT_X1 && x < BTN_EXIT_X2 && y > BTN_EXIT_Y1 && y < BTN_EXIT_Y2 );
	}
};

