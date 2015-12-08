#pragma once

#include <SDL.h>

class EventManager {
public:
	EventManager();
	~EventManager();

	void updateEvents();

	bool hasEnded() const { return ended; }
	bool isKeyPressed(const SDL_Scancode keyCode) const { return keys[keyCode]; }
	bool isMousePressed(const Uint8 button) const { return mouseButtons[button]; }
	bool isMouseMoving() const { return ((xRel != 0) && (yRel != 0)); }
	int getX() const { return x; }
	int getY() const { return y; }
	int getXRel() const { return xRel; }
	int getYRel() const { return yRel; }
	void showCursor(bool show) const { SDL_ShowCursor(show); }
	void captureCursor(bool capture) const { SDL_SetRelativeMouseMode((SDL_bool)capture); }

private:
	SDL_Event events;
	bool keys[SDL_NUM_SCANCODES];
	bool mouseButtons[8];

	bool ended;
	int x, y, xRel, yRel;

};

