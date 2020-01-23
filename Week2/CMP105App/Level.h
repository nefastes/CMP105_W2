#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level {
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput();
	void update();
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Add your object here
	sf::Font font;
	sf::Text text;

	sf::Vector2f startMousePos;
	sf::Vector2f endMousePos;
	bool drag = false;
	bool resultDisplayed = false;

	bool renderCircle = false;
	sf::CircleShape circle;

	int index = 0;
	bool next = true;
	int konami[11] = {
						sf::Keyboard::Up,sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Down,sf::Keyboard::Left,
						sf::Keyboard::Right,sf::Keyboard::Left,sf::Keyboard::Right,sf::Keyboard::B,sf::Keyboard::A,
						sf::Keyboard::Enter
	};
};