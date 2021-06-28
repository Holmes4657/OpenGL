#include "shader.h"

void shader_errors(GLuint obj, const char* type);

void loading_shader(const GLchar* filepath, GLchar** shaderType) {

    FILE* file = fopen(filepath, "rb");
    if(file == NULL) {
        printf("File not found\n");
        exit(0);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    *shaderType = malloc(fileSize + 1);
    if (shaderType == NULL) {
        printf("ERROR:: Allocation error\n");
        exit(0);
    }

    fread(*shaderType, fileSize, 1, file);
    if (feof(file)) {
        printf("ERROR:: Unexpected end of file\n");
        exit(0);
    }

    fclose(file);

    (*shaderType)[fileSize] = 0;
}

void compile_shader(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint* shaderProgram) {

    GLuint vertexShader, fragmentShader;

    GLchar* vertexShaderSource;
    GLchar* fragmentShaderSource;

    loading_shader(vertexPath, &vertexShaderSource);
    loading_shader(fragmentPath, &fragmentShaderSource);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar* const*)&vertexShaderSource, NULL);
    glCompileShader(vertexShader); //Compile
    shader_errors(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar* const*)&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    shader_errors(fragmentShader, "FRAGMENT");

    *shaderProgram = glCreateProgram();

    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    shader_errors(*shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void shader_errors(GLuint obj, const char* type) {
    int success;
    char infoLog[512];

    if (strcmp(type, "VERTEX") == 0) {
        glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(obj, 512, NULL, infoLog);
            printf("ERROR::SHADER::%s::COMPILATION_FAILED %s\n", type, infoLog);
        }
        else {
            printf("Shader %s loaded\n", type);
        }
    }
    else {
        if (strcmp(type, "FRAGMENT") == 0) {
            glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(obj, 512, NULL, infoLog);
                printf("ERROR::SHADER::%s::COMPILATION_FAILED %s\n", type, infoLog);
            }
            else {
                printf("Shader %s loaded\n", type);
            }
        }
        else {
            if (strcmp(type, "PROGRAM") == 0) {
                glGetProgramiv(obj, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(obj, 512, NULL, infoLog);
                    printf("ERROR::SHADER::%s::LINKING_FAILED %s\n", type, infoLog);
                }
                else {
                    printf("Program loaded\n");
                }
            }
        }
    }
}