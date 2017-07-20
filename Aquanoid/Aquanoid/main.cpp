//Hide console of Windows Application:
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Controller.h"

//---------------------------------------Main----------------------------------------//

int main()
{
	std::srand(static_cast<unsigned int>( std::time(NULL) ));

	int const SCREEN_WIDTH = 900;
	int const SCREEN_HEIGHT = 800;


	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH , SCREEN_HEIGHT) , "~~~ Aquanoid ~~~");
	
	Controller controller(window);


	return EXIT_SUCCESS;
}
