#pragma once

#ifndef STRUCTS_H
#define STRUCTS_H

#ifdef _WIN64
	#include <SDL.h>
#elif __linux
	#include <SDL2/SDL.h>
#endif

#include <GL/glew.h>

/*typedef struct MainSystems {
	SDL_Window* window;
	SDL_GLContext glContext;
} MainSystems;*/

#endif // !STRUCTS_H