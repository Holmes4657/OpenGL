#include "model.h"

#define MAX_VERTEX	100000
#define MAX_NORMAL	100000
#define MAX_UV		100000

struct Vertex {
  float x, y, z;
};

struct Normal {
  float x, y, z;
};

struct UV {
  float x, y;  
};

struct All {
  struct Vertex v;
  struct UV t;
  struct Normal n;
};

static void print_info(struct All* All) {
  printf("%.4f %.4f %.4f %.4f %.4f %.4f %.4f %.4f\n",
	   All->v.x, All->v.y, All->v.z,
	   All->t.x, All->t.y,
	   All->n.x, All->n.y, All->n.z);
}

void load_obj(const char* filename, vec3 vertices, vec3 uvs, vec3 normals) {
  /* Local */
  float x, y, z;

  unsigned int v[3], u[3], n[3];
  unsigned int vi = 1;
  unsigned int ni = 1;
  unsigned int ti = 1;

  struct Vertex * Vertex;
  struct Normal * Normal;
  struct UV * UV;
  struct All All;

  /* Memory allocation */
  Vertex = malloc(MAX_VERTEX * sizeof(struct Vertex));
  Normal = malloc(MAX_NORMAL * sizeof(struct Normal));
  UV = malloc(MAX_UV * sizeof(struct UV));

  FILE *file = fopen(filename, "r");
  if(file == NULL) {
    printf("File not found\n");
  }

  while(1) {
    char lineheader[128];
    int res = fscanf(file, "%s", lineheader);
    if(res == EOF) {
      break;
    }

    if(strcmp(lineheader, "v") == 0) {
      fscanf(file, "%f %f %f\n", &x, &y, &z);

      /* Push to array */
      Vertex[vi].x = x;
      Vertex[vi].y = y;
      Vertex[vi].z = z;
      vi++;
    }
    else if(strcmp(lineheader, "vt") == 0) {
      fscanf(file, "%f %f\n", &x, &y);
      
      UV[ti].x = x;
      UV[ti].y = y;
      ti++;
    }
    else if(strcmp(lineheader, "vn") == 0) {
      fscanf(file, "%f %f %f\n", &x, &y, &z);

      Normal[ni].x = x;
      Normal[ni].y = y;
      Normal[ni].z = z;
      ni++;
    }
    else if(strcmp(lineheader, "f") == 0) {
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v[0], &u[0], &n[0],
                                                                  &v[1], &u[1], &n[1],
                                                                  &v[2], &u[2], &n[2]);

      if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return;
			}

      All.v = Vertex[v[0]];
      All.t = UV[u[0]];
      All.n = Normal[n[0]];

      vertices[0] = All.v.x;
      uvs[0] = All.t.x;
      normals[0] = All.n.x;

      print_info(&All);

      All.v = Vertex[v[1]];
      All.t = UV[u[1]];
      All.n = Normal[n[1]];

      vertices[1] = All.v.x;
      uvs[1] = All.t.x;
      normals[1] = All.n.x;

      print_info(&All);

      All.v = Vertex[v[2]];
      All.t = UV[u[2]];
      All.n = Normal[n[2]];

      vertices[2] = All.v.x;
      uvs[2] = All.t.x;
      normals[2] = All.n.x;

      print_info(&All);
    }
  }

  fclose(file);
}