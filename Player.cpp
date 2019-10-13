#include "Player.h"

PlayerClass::PlayerClass()
{
}

void PlayerClass::Move()

{
	//Gets the keyboard inputs and assigns them a direction while it won't let them double back on itself
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && Direction != Directions::East)
		Direction = (Directions::West);
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && Direction != Directions::West)
		Direction = (Directions::East);
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && Direction != Directions::South)
		Direction = (Directions::North);
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && Direction != Directions::North)
		Direction = (Directions::South);

	//Moving the snake the same distance as its radius using the enums and defining them
	switch (Direction)
	{
	case Directions::North:
		ScreenPos.y -= 2 * Radius;
		break;
	case Directions::South:
		ScreenPos.y += 2 * Radius;
		break;
	case Directions::East:
		ScreenPos.x += 2 * Radius;
		break;
	case Directions::West:
		ScreenPos.x -= 2 * Radius;
		break;
	case Directions::Stop:
		break;
	case Directions::Start:
		break;
	}

	//Make the snake move by adding one to the front and removing one from the back
	body.push_front(ScreenPos);

	//This is how the snake moves, it will continually add one to the front and pop one from the back
	//However when the snake collides with the food, the growAmount will change to that and will continually add that amount
	if (growAmount > 0)
		growAmount--;
	else
		body.pop_back();
}

void PlayerClass::DisplaySnake(sf::RenderWindow & window)
{
	displayscore[0].setFont(font);
	displayscore[0].setString("Score " + std::to_string(score));
	displayscore[0].setFillColor(sf::Color::Blue);
	displayscore[0].setPosition(sf::Vector2f(900 / 22, 900 / 22 * 1));

	for (int i = 0; i < 1; i++)
		window.draw(displayscore[i]);

	displayAir[0].setFont(font);
	displayAir[0].setString("Air Remaining " + std::to_string(Air));
	displayAir[0].setFillColor(sf::Color::Blue);
	displayAir[0].setPosition(sf::Vector2f(900 / 3, 900 / 22 * 1));

	for (int i = 0; i < 1; i++)
		window.draw(displayAir[i]);
}

void PlayerClass::EndGame(sf::RenderWindow & window)
{
	displayscore[1].setFont(font);
	displayscore[1].setString("GAME OVER");
	displayscore[1].setFillColor(sf::Color::Red);
	displayscore[1].setPosition(sf::Vector2f(900 / 3, 900 / 4 * 1));


	displayscore[2].setFont(font);
	displayscore[2].setString("Score " + std::to_string(score));
	displayscore[2].setFillColor(sf::Color::White);
	displayscore[2].setPosition(sf::Vector2f(900 / 3, 900 / 4 * (float)1.5));

	for (int i = 1; i < 3; i++)
		window.draw(displayscore[i]);
}
