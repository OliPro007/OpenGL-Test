#include "EventManager.h"

EventManager::EventManager():
x(0), y(0), xRel(0), yRel(0), ended(false) {
	for(int i = 0; i < SDL_NUM_SCANCODES; i++)
		keys[i] = false;

	for(int i = 0; i < 8; i++)
		mouseButtons[i] = false;
}

EventManager::~EventManager() {}

void EventManager::updateEvents() {
	xRel = 0.0;
	yRel = 0.0;

	while(SDL_PollEvent(&events)) {
		switch(events.type) {
			case SDL_WINDOWEVENT:
				if(events.window.event == SDL_WINDOWEVENT_CLOSE)
					ended = true;
				break;

			case SDL_KEYDOWN:
				keys[events.key.keysym.scancode] = true;
				break;

			case SDL_KEYUP:
				keys[events.key.keysym.scancode] = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseButtons[events.button.button] = true;
				break;

			case SDL_MOUSEBUTTONUP:
				mouseButtons[events.button.button] = false;
				break;

			case SDL_MOUSEMOTION:
				x = events.motion.x;
				y = events.motion.y;
				xRel = events.motion.xrel;
				yRel = events.motion.yrel;
				break;
		}
	}
}