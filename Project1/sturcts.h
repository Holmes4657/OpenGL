#pragma once

#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL.h>
#include <GL/glew.h>

typedef struct {
	SDL_Window* window;
	SDL_GLContext* glContext;
} MainSystems;

#endif // !STRUCTS_H