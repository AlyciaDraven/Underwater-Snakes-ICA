#include "Snake.h"

//Constructor
Snake::Snake()
{   //The reason why we divide the Position by 20 and times by 20 is due to the fact that we need the window to be a grid that is 
	// double the radius of the snake
	//static casting - converting between types
	ScreenPos = (sf::Vector2f( (float) ((400 / 20) * 20) , (float) ((400 / 20) * 20)) );
	Colour = (sf::Color(1, 1, 255, 255));
	Radius = 10;
	isAlive = true;

	body.push_front(ScreenPos);

	if (!font.loadFromFile("snakebold.ttf"))
	{
		//handle error
	}
}

//Render function that will display the snake head to the window
void Snake::Render(sf::RenderWindow & window)
{
	//Create an instance of the SFML CircleShape
	sf::CircleShape Snakes(Radius);

	//Sets the FillColour to what we have passed through: Colour
	Snakes.setFillColor(Colour);

	for (auto p : body)
	{
		//Sets the position to what we have passed through: ScreenPos
		Snakes.setPosition(p);
		//Draw our circle shape to the window
		window.draw(Snakes);
	}
}

//Function that will command how the snake moves
void Snake::Move()
{
	//If this is seen then this function has not been overwritten so must be checked
	cout << "if this is seen check it" << endl;
}

//This is all the collisions within the game, including the tank, itself and the food
void Snake::Collision(std::vector<Collectables*>& Food)
{	
	//Bounces the snake off of the windows - window collision
	if (ScreenPos.x < 0)
	{
		Direction = Directions::Stop;
		isAlive = false;
	}
	else if (ScreenPos.y < 0)
	{
		Direction = Directions::Stop;
		isAlive = false;
	}
	else if (ScreenPos.x > 900 - (2 * Radius))
	{
		Direction = Directions::Stop;
		isAlive = false;
	}
	else if (ScreenPos.y > 900 - (2 * Radius))
	{
		Direction = Directions::Stop;
		isAlive = false;
	}

	//Check for collision with food
	for (auto &food : Food)
	{
		//If the head of the snake is in the same position as a collectable and they are also alive
		if (getPosition() == food->getPosition() && food->Alive() == true)
		{
			//Changes the grow amount to the random score of that food and will update the snake body
			growAmount = food->getScore();
			//Kills the food so it can go through the vector and respawn
			food->ChangeState();
		}	
	}

	//the iterator will need to start at the the second segment if there is one
	//and compares the second segment to compare with the first
	//and if it is the same a collision has been detected and will kill the snake
	auto iter = body.begin();
	iter++;
	while (iter != body.end())
	{
		if (*iter == getPosition())
		{
			isAlive = false;
		}
		iter++;
	}
}

sf::Vector2f Snake::getPosition()
{
	return ScreenPos;
}

//Checks whether the snake is alive or dead
bool Snake::Alive()
{
	if (isAlive == true)
		return true;
	else
		return false;
}

//The update function will continually run
void Snake::Update(sf::RenderWindow & window, std::vector<Collectables*>& Food)
{
	score = body.size() - 1;
	
	Move();
	Collision(Food);
	Alive();
	DisplaySnake(window);

	Air--;
	if (Air <= 0)
	{
		body.pop_back();
		if (body.size() == 1)
		{
			Kill();
			score = score - 1;
		}
	}
}

//Displays the score and continually updates it through the update function
void Snake::DisplaySnake(sf::RenderWindow & window)
{
	//If this is seen then this function has not been overwritten so must be checked
	cout << "if this is seen check it" << endl;
}

//Displays the final score
void Snake::EndGame(sf::RenderWindow & window)
{
	//If this is seen then this function has not been overwritten so must be checked
	cout << "if this is seen check it" << endl;
}

void Snake::Kill()
{
	isAlive = false;
}


