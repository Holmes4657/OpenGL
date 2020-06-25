#pragma once

#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL.h>
#include <GL/glew.h>

typedef struct {
	SDL_Window* window;
	SDL_GLContext* glContext;
} MainSystems;

struct Vector3D {
	float x;
	float y;
	float z;
};

#endif // !STRUCTS_H