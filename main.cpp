/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>
#include "Game.h"

using namespace std;

int main()
{	//initialises random seed
	//static casting - converting between types
	srand((unsigned int)time(NULL));

	// Create an instance of the SFML RenderWindow type which represents the display
	// and initialise its size and title text
	sf::RenderWindow window(sf::VideoMode(900, 900), "C++ Snake ICA : T7022349");

	// We can still output to the console window
	cout << "SnakeGame: Starting" << endl;

	//Dynamic Memory to allocate a chunk of stack memory
	Game* SnakeGame = new Game();


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}
		
		SnakeGame->Update(window);

		//If the game is restarted it will delete the Dynamic memory stack and create a new one
		//Which resets all of the values
		if (SnakeGame->GetState() == GameMode::Restart_Game_State)
		{
			delete SnakeGame;
			Game* SnakeGame = new Game();

		}
	}
	
	std::cout << "SnakeGame: Finished" << std::endl;

	//Deletes the memory
	delete SnakeGame;

	return 0;
	
}
