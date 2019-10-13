#include "WaterTank.h"

//Constuctor
Water::Water()
{
	//Sets the water variables
	Size = (sf::Vector2f((float)900,(float)900));

	ScreenPosition = (sf::Vector2f((float)0, (float)200));

	Colour = sf::Color::Cyan;
}

void Water::Render(sf::RenderWindow & window)
{
	sf::RectangleShape Water(Size);

	Water.setPosition(ScreenPosition);

	Water.setFillColor(Colour);

	window.draw(Water);

}

int Water::Timer()
{
	return Count;
}

void Water::Restart()
{
	Count = 27;
}

//Constantly looped
void Water::Update(sf::RenderWindow& window)
{
	
	Timer();
	Count--;
}
