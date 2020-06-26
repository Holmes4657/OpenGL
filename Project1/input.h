#pragma once

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "camera.h"

/* Keyboard */
const Uint8* keystate;

/* Input */
void keyboard_handling(double deltaTime);
void mouse_handling(SDL_MouseMotionEvent event);
void scroll_handling(SDL_MouseWheelEvent event);

#endif // !INPUT_H