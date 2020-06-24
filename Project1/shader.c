#include "shader.h"

GLuint* vertexShaderSource = 
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\n\0";

GLuint* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"// texture samplers\n"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main()\n"
"{\n"
"// linearly interpolate between both textures (80% container, 20% awesomeface)\n"
"FragColor = texture(texture1, TexCoord);\n"
"}\n\0";

/*
 *  Compilation of the shader obtained from the file for use in the program
 */
void compile_shader(GLuint* shaderProgram) {
    GLuint vertexShader, fragmentShader;

    //Work with vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER); //Shader type
    glShaderSource(vertexShader, 1, (const GLchar* const*)&vertexShaderSource, NULL); //Bind
    glCompileShader(vertexShader); //Compile

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar* const*)&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    *shaderProgram = glCreateProgram();

    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    //Unload since the shader is already loaded into the program and is not used
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}