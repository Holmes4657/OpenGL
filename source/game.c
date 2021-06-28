#include "game.h"

SDL_Window *window = NULL;
SDL_GLContext glContext = NULL;

bool gameInit(void) {

	SDL_Log("Initialization of SDL has begun\n");

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error", "Unable to initialize SDL: %s", window);

		return false;
	}
	else {
		SDL_Log("SDL initialized successfully\n");
	}

	window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (window == NULL) {
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error", "Could not create window: %s", window);

		return false;
	}

	glContext = SDL_GL_CreateContext(window);

	if (glContext == NULL) {
		SDL_Log("Cound not create context: %s", SDL_GetError());

		return false;
	}

	SDL_Log("Initialization of OpenGL has begun\n");

	glewExperimental = 1;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		printf("Error: %s\n", glewGetErrorString(err));
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error", "Not possible to start GLEW", window);
		return false;
	}
	else {
		SDL_Log("GLEW successfully initialized\n");
	}

	printf("\nOpenGL version: %s\n", glGetString(GL_VERSION));
	printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer device: %s\n\n", glGetString(GL_RENDERER));
	
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(0);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, 800, 600);

	return true;
}

void swap_window(void) {
	SDL_GL_SwapWindow(window);
}

void cleanUp(void) {
	SDL_GL_DeleteContext(glContext);
	glContext = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}