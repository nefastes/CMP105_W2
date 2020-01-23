// Input class
// Class stores the current state on keyboard and mouse input.
// Store which keys are pressed or released, mouse position and mouse button presses.
// @author Paul Robertson

#pragma once

class Input
{
private:
	// Mouse structure, store mouse relevant information
	struct Mouse
	{
		int x = 0, y = 0;
		bool left = false, right = false;
	};

public:
	// Functions for setting key as pressed, released and checking current state.
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);
	void setKeyCode(int key);
	int getKeyCode();

	// Functions are mouse input, including getting and setting current position and mouse button presses.
	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	int getMouseX();
	int getMouseY();
	void setMouseLDown(bool down);
	bool isMouseLDown();
	void setMouseRDown(bool down);
	bool isMouseRDown();
	
private:
	// Array of booleans representing keys (pressed = true, released = false)
	bool keys[256]{ false };
	// Mouse variable
	Mouse mouse;
	//Key code
	int code;
};
