#ifndef INPUT_H
#define INPUT_H

#ifdef _WIN64
	#include <SDL.h>
#elif __linux
	#include <SDL2/SDL.h>
#endif

#include "camera.h"

/* Input */
void keyboard_handling(const Uint8* keystate, double deltaTime);
void mouse_handling(SDL_MouseMotionEvent event);
void scroll_handling(SDL_MouseWheelEvent event);

#endif // !INPUT_H