#include "input.h"

void keyboard_handling(double deltaTime) {
	if (keystate[SDL_SCANCODE_Q]) {
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent(&quit);
		return;
	}

	if (keystate[SDL_SCANCODE_W]) {
		ProcessKeyboard(FORWARD, (float)deltaTime);
	}

	if (keystate[SDL_SCANCODE_S]) {
		ProcessKeyboard(BACKWARD, (float)deltaTime);
	}

	if (keystate[SDL_SCANCODE_A]) {
		ProcessKeyboard(LEFT, (float)deltaTime);
	}

	if (keystate[SDL_SCANCODE_D]) {
		ProcessKeyboard(RIGHT, (float)deltaTime);
	}
}

void mouse_handling(SDL_MouseMotionEvent event) {
	ProcessMouseMovement((float)event.xrel, (float)-event.yrel, true);
}


void scroll_handling(SDL_MouseWheelEvent event) {
	ProcessMouseScroll((float)event.y);
}