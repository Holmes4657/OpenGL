#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <stdbool.h>

void loadTexture(const char* filename, GLuint* texture);

#endif // !TEXTURE_H