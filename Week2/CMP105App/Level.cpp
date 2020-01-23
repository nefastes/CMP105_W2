#include "Level.h"
#include "math.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf")) std::cout << "Could not load font.\n";
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(0, 0);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	//if W is pressed, output it to the console
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W was pressed !" << std::endl;
	}

	//if J,K & L are pressed together, output it to the console
	if (input->isKeyDown(sf::Keyboard::J))
	{
		if (input->isKeyDown(sf::Keyboard::K))
		{
			if (input->isKeyDown(sf::Keyboard::L))
			{
				input->setKeyUp(sf::Keyboard::J);
				input->setKeyUp(sf::Keyboard::K);
				input->setKeyUp(sf::Keyboard::L);
				std::cout << "J,K & L are pressed together." << std::endl;
			}
		}
	}

	//Closes when ESC is pressed
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}

	//Calaculate drag when left click
	if (input->isMouseLDown() && !drag)
	{
		startMousePos = sf::Vector2f(input->getMouseX(), input->getMouseY());
		drag = true;
	}
	else if (drag)
	{
		endMousePos = sf::Vector2f(input->getMouseX(), input->getMouseY());
		if (!input->isMouseLDown())
		{
			drag = false;
			resultDisplayed = false;
		}
	}
	else if(!resultDisplayed)
	{
		float deltaY = endMousePos.y - startMousePos.y;
		float deltaX = endMousePos.x - startMousePos.x;
		float distanceBetweenPos = sqrt(deltaY * deltaY + deltaX * deltaX);
		std::cout << "The distance of the drag is " << distanceBetweenPos << " !" << std::endl;
		resultDisplayed = true;
	}
}

// Update game objects
void Level::update()
{
	//Update and output the current mouse postion
	mouseString = "Current Position: ";
	mouseString += std::to_string(input->getMouseX());
	mouseString += ",";
	mouseString += std::to_string(input->getMouseY());
	text.setString(mouseString);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(text);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}