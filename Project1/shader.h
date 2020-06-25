#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compile_shader(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint* program);

#endif // !SHADER_H