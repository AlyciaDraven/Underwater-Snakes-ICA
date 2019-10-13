#pragma once

#include <SFML/Graphics.hpp>

class Water
{
private:
	sf::Vector2f Size;
	sf::Vector2f ScreenPosition;
	sf::Color Colour;
	int Count{ 15 };

public:
	Water();
	void Render(sf::RenderWindow& window);
	sf::Vector2f GetLevel() { return ScreenPosition; };
	void ReduceWaterLevel() { ScreenPosition.y += 20; };
	int Timer();
	void Restart();
	//Update function that will be continuously looped
	void Update(sf::RenderWindow& window);
};