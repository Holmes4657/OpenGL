#pragma once

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include "structs.h"

bool gameInit(void);
void cleanUp(void);

#endif // !GAME_H