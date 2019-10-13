#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Collectables.h"
#include "WaterTank.h"

enum class GameMode
{
	Menu_State,
	In_Game_State,
	End_Game_State,
	Restart_Game_State
};

class Game 
{
private:

	sf::Vector2f Size;
	sf::Vector2f ScreenPosition;
	sf::Color Colour;

	//Instances from other classes
	PlayerClass PlayerSnake;

	Collectables Food;
	Water water;

	GameMode gamemode{GameMode::Menu_State};
	sf::Font font;
	sf::Text menu[2];
	sf::Text title[1];
	int SelectedIndexOption{ 0 };
public:
	//constructor
	Game();
	void Render(sf::RenderWindow& window);
	//Update function that will be continuously looped
	void Update(sf::RenderWindow& window);
	void MainMenu(sf::RenderWindow& window);
	void Run(sf::RenderWindow& window);
	void GameOver(sf::RenderWindow& window);
	void Restart(sf::RenderWindow& window);
	int GetPressedItem() { return SelectedIndexOption; };
	GameMode GetState() { return gamemode; };
	void MoveUp();
	void MoveDown();

};

