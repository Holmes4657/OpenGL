#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cglm/cglm.h>

void load_obj(const char* filename, vec3 vertices, vec3 uvs, vec3 normals);

#endif // !MODEL_H