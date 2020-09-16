#pragma once

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN64
	#include <SDL.h>
#elif __linux
	#include <SDL2/SDL.h>
#endif

#include "structs.h"

bool gameInit(void);
void swap_window(void);
void cleanUp(void);

#endif // !GAME_H