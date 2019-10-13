#include "Game.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//Constructor
Game::Game()
{

	Size = (sf::Vector2f((float)900, (float)900));
	ScreenPosition = (sf::Vector2f(0.f,0.f));
	Colour = sf::Color::Black;

	if (!font.loadFromFile("snakebold.ttf"))
	{
		//handle error
	}

	title[0].setFillColor(sf::Color::Cyan);

	//The default menu colours
	menu[0].setFillColor(sf::Color::Blue);
	menu[1].setFillColor(sf::Color::White);

	PlayerSnake = PlayerClass();
}

void Game::Render(sf::RenderWindow & window)
{
	sf::RectangleShape Screen(Size);

	Screen.setPosition(ScreenPosition);

	Screen.setFillColor(Colour);

	window.draw(Screen);
}

//This function is constantly called in the main() and will run the corresponding code depending on what GameMode is active
void Game::Update(sf::RenderWindow & window)
{
	switch (gamemode)
	{
	case GameMode::Menu_State:
		MainMenu(window);
		window.clear();
		break;

	case GameMode::In_Game_State:
		Run(window);
		window.clear();
		break;

	case GameMode::End_Game_State:
		GameOver(window);
		window.clear();
		break;
	case GameMode::Restart_Game_State:
		Restart(window);
		window.clear();
		break;

	default:
		break;
	}
}

//This is the main menu function
void Game::MainMenu(sf::RenderWindow & window)
{
	//We set what the menu and title array are so they can be displayed
	title[0].setFont(font);
	title[0].setString("Underwater Snakes");
	title[0].setScale(2.f, 2.f);
	title[0].setPosition(sf::Vector2f(900 / 6, 900 / 4 * (float)1.5));

	menu[0].setFont(font);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(900 / (float)2.5, 900 / 4 * 2));

	menu[1].setFont(font);
	menu[1].setString("Exit");
	menu[1].setPosition(sf::Vector2f(900 / (float)2.5, 900 / 4 * (float)2.5));

	while (window.isOpen() && gamemode == GameMode::Menu_State)
	{
		Render(window);

		window.draw(title[0]);

		//This renders the text on screen
		for (int i = 0; i < 2; i++)
			window.draw(menu[i]);
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//if the event is a key being pressed	
				case sf::Event::KeyReleased:

					//and depending on which key has been pressed will call a function which differs for the keys intention
					switch (event.key.code)
					{
					case (sf::Keyboard::Up):
						MoveUp();
						//Instead of forcing termination like the break, a continue forces the next iteration
						//of the loop to begin
						continue;

					case (sf::Keyboard::W):
						MoveUp();
						continue;

					case (sf::Keyboard::Down):
						MoveDown();
						continue;

					case(sf::Keyboard::S):
						MoveDown();
						continue;

						//If Enter is pressed and depending on the id of the choice it will run 
						case sf::Keyboard::Return:
							switch (SelectedIndexOption)
							{
							case 0:
								gamemode = GameMode::In_Game_State;
								break;

							case 1:
								window.close();
								break;

							default:
								break;
							}

					default:
						continue;

					continue;
					}

				case sf::Event::Closed:
					window.close();
					break;

				default:
					break;
			}

		}
		window.display();
	}
	window.clear();
}

//This function is called when the play button is pressed
void Game::Run(sf::RenderWindow & window)
{
	//initialises random seed
	//static casting - converting between types
	srand((unsigned int)time(NULL));

	//This will hold the Collectables
	vector<Collectables*> Food;

	//Populating all 5 of the food into the vector
	for (int i = 0; i < 5; i++)
		Food.push_back(new Collectables());

	// Main loop that continues until we call window.close()
	while (window.isOpen() && gamemode == GameMode::In_Game_State)
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

		//This renders the water before anything else otherwise it would hide the snake and the food
		water.Render(window);
		water.Update(window);

		//This continually updates the water and lowers it according to the timer
		if (water.Timer() == 0)
		{
			water.ReduceWaterLevel();
			water.Restart();
		}

		//Draws the Snake instance Bob
		PlayerSnake.Render(window);

		//This function is continually called to allow the snake to use multiple functions through one
		PlayerSnake.Update(window, Food);

		//There is a 1 in a 20 chance to spawn
		if (rand() % 10 == 0)
		{
			for (Collectables* C : Food)
			{
				if (!C->Alive())
				{
					//Changes the food to alive
					C->Spawn();

					//If the collectables try and spawn in a position where there is already one alive or if it is above the water it will randomise the position
					if (C->getPosition() == C->getPosition() && C->Alive() == true)
					{
						C->ChangePosition();
					}

					//If the collectables are spawned above the water level, it will immediately kill them and so they won't be rendered to the screen
					if (C->getPosition().y < water.GetLevel().y)
					{
						C->ChangeState();
					}

					break;
				}

			}
		}		

		//If the Player is over two head sizes above the water level it will die
		if (PlayerSnake.getPosition().y < water.GetLevel().y - 60)
			PlayerSnake.Kill();

		if (PlayerSnake.getPosition().y < water.GetLevel().y)
			PlayerSnake.FillAir();

		//This displays the collectables with this being Equivalent to (*Collectables).render(window)
		for (Collectables *Collectables : Food)
			Collectables->Render(window);

		//If the snake is killed it will immediately set the gamemode to end game which will then be called from the update function
		if (PlayerSnake.Alive() == false)	
			gamemode = GameMode::End_Game_State;

		sf::Clock clock;
		// Loop until time passed
		//The reason it is so fast is that if it was slower it would take longer to react from the key pressed
		while (clock.getElapsedTime().asMilliseconds() < 100);
		clock.restart();

		// Get the window to display its contents
		window.display();
		window.clear();
	}

}

//This function is called when the gamemode is set to End_Game
void Game::GameOver(sf::RenderWindow & window)
{
	// Main loop that continues until we call window.close()
	if(window.isOpen() && gamemode == GameMode::End_Game_State)
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

		//Displays the players score
		PlayerSnake.EndGame(window);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			gamemode = GameMode::Restart_Game_State;
		

		window.display();
		window.clear();
	}

}

void Game::Restart(sf::RenderWindow & window)
{
	// Main loop that continues until we call window.close()
	while (gamemode == GameMode::Restart_Game_State)
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

		window.display();
		window.clear();
	}
	
}

//When this function is called it will set the previous Index to white and the one above it to blue
void Game::MoveUp()
{
	if (SelectedIndexOption - 1 >= 0)
	{
		menu[SelectedIndexOption].setFillColor(sf::Color::White);
		SelectedIndexOption--;
		menu[SelectedIndexOption].setFillColor(sf::Color::Blue);
	}
}

//When this function is called it will set the previous Index to white and the one below it to blue
void Game::MoveDown()
{
	if (SelectedIndexOption + 1 < 3)
	{
		menu[SelectedIndexOption].setFillColor(sf::Color::White);
		SelectedIndexOption++;
		menu[SelectedIndexOption].setFillColor(sf::Color::Blue);
	}
}

