#pragma once
#include <SFML/Graphics.hpp>
#include "Collectables.h"
#include <list>
#include <iostream>

using namespace std;

enum class Directions
{
	North,
	East,
	South,
	West,
	Stop,
	Start
};

class Snake
{

protected:
	//a simple class that defines a mathematical vector with two coordinates that contain the screen x and y position
	sf::Vector2f ScreenPos;
	//a simple colour class composed of 4 components: Red, Green, Blue and Alpha
	sf::Color Colour;
	float Radius;
	//This will start the snake in a stationary position
	Directions Direction{ Directions::Start };
	int growAmount{ 0 };
	std::list <sf::Vector2f> body;
	bool isAlive;	
	size_t score;
	sf::Font font;
	sf::Text displayscore[3];
	sf::Text displayAir[1];
	int Air{ 100 };

public:
	//Constructor
	Snake();
	//Render function
	void Render(sf::RenderWindow& window);
	virtual void Move() = 0;
	//Collision function
	void Collision(std::vector<Collectables*>& Food);
	//return function to get the position of the snake
	sf::Vector2f getPosition();
	//function to that returns if the snake is alive or not
	bool Alive();
	//Update function that will be continuously looped
	void Update(sf::RenderWindow& window, std::vector<Collectables*>& Food);
	//This will display the players score
	virtual void DisplaySnake(sf::RenderWindow& window) = 0;
	virtual void EndGame(sf::RenderWindow& window) = 0;
	void Kill();
	void FillAir() { Air = 100;	};

};
