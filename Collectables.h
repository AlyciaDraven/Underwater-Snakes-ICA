#pragma once
#include <SFML/Graphics.hpp>
#include "WaterTank.h"

class Collectables
{
private:
	Water water;
	//a simple class that defines a mathematical vector with two coordinates that contain the screen s and y position
	sf::Vector2f ScreenPos;
	//a simple colour class composed of 4 components: Red, Green, Blue and Alpha
	sf::Color Colour;
	float Radius;
	int Score;
	bool isAlive;

public:
	//Default Constructor
	Collectables();
	//Render function
	void Render(sf::RenderWindow& window);
	//Returns whether the collectable is alive or not
	bool Alive();
	//Shows if they have been 'eaten'/'killed' by changing the status of isAlive
	void ChangeState();
	//Sets the collectable to alive as it is drawn to the window
	void Spawn() { isAlive = true; };
	void ChangePosition() { ScreenPos = (sf::Vector2f((float)(((rand() % 800) / 20) * 20) , ((float)((rand() % 1000) / 20) * 20)));
	};
	sf::Vector2f getPosition() { return ScreenPos; };
	int getScore() { return Score; }
};