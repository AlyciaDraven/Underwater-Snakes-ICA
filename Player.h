#pragma once
#include "Snake.h"

class PlayerClass : public Snake
{

public:
	PlayerClass();

	//Function to let the snake move
	virtual void Move() override;
	virtual void DisplaySnake(sf::RenderWindow& window) override;
	virtual void EndGame(sf::RenderWindow& window) override;
};