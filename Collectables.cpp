#include "Collectables.h"

//Constructor
Collectables::Collectables()
{
	//The reason why we divide the Position by 20 and times by 20 is due to the fact that we need the window to be a grid that is 
	// double the radius of the snake
	ScreenPos = (sf::Vector2f((float)(((rand() % 800) / 20) * 20), ((float)((rand() % 1000) / 20) * 20)));
	Colour = (sf::Color(255, 255, 1, 255));
	Radius = 10;
	Score = (rand() % 4 + 1);
	isAlive = false;
}

//Render function that will override the parent class' function
void Collectables::Render(sf::RenderWindow & window)
{
	//If the Collectable is false then it will not render to the window
	if (isAlive == false)
		return;

	// Create an instance of the SFML RectangleShape
	sf::CircleShape Collectable(Radius);

	//Sets the position to what we have passed through: ScreenPos
	Collectable.setPosition(ScreenPos);

	//Sets the FillColour to what we have passed through: Colour
	Collectable.setFillColor(Colour);

	// draw our circle shape to the window
	window.draw(Collectable);
}

//Checks whether the collectables are alive or not so if the Collectables are returned true then they are set to true otherwise they are set to false/dead
bool Collectables::Alive()
{
	if (isAlive == true)
		return true;
	else
		return false;
}

//This function will check what state the Food is in and will flip it around
void Collectables::ChangeState()
{
	if (isAlive == true)
		isAlive = false;
	else
		isAlive = true;
}
