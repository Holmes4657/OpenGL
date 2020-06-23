#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void loadTexture(const char* filename, GLuint* texture) {
    //Variables
    int textureWidth, textureHeight, nrChannels;
    unsigned char* data;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    data = stbi_load(filename, &textureWidth, &textureHeight, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        printf("Texture %s loaded\n", filename);
    }
    else {
        printf("Failed to load texture\n");
    }
    stbi_image_free(data);
}