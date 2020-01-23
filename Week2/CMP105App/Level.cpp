#include "Level.h"
#include "math.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	//Mouse pos string
	if (!font.loadFromFile("font/arial.ttf")) std::cout << "Could not load font.\n";
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(0, 0);

	//Circle
	circle.setRadius(10);
	circle.setFillColor(sf::Color::Yellow);
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
	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "J,K & L are pressed together." << std::endl;
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

	//Render a circle on right click
	if (input->isMouseRDown()) renderCircle = true;
	else renderCircle = false;

	//Konami code
	if (next && input->getKeyCode() != -1)
	{
		if (input->getKeyCode() == konami[index])
		{
			std::cout << "Made it this far" << std::endl;
			std::cout << index << std::endl;
			++index;
			next = false;
		}
		else if (input->getKeyCode() != konami[index])
		{
			index = 0;
			next = false;
		}
	}
	else if (index == 11)
	{
		std::cout << "You did the konami code !" << std::endl;
	}
	else if (!input->isKeyDown(input->getKeyCode()))
	{
		next = true;
		input->setKeyCode(-1);
	}
}

// Update game objects
void Level::update()
{
	//Update and output the current mouse postion
	text.setString("Current Position: " + std::to_string(input->getMouseX()) + "," + std::to_string(input->getMouseY()));

	//Update circle pos
	if(renderCircle) circle.setPosition(input->getMouseX(), input->getMouseY());
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(text);
	window->draw(circle);
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