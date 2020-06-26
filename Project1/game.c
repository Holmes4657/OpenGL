#include "game.h"

MainSystems mainSystems;

#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048

bool gameInit(void) {

	GLint total_mem_kb = 0;

	printf("Initialization of SDL has begun\n");

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error", "Unable to initialize SDL: %s", mainSystems.window);

		return false;
	}
	else {
		printf("SDL initialized successfully\n");
	}

	//OpenGL 3.3
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, SDL_TRUE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//24 bit Z buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mainSystems.window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (mainSystems.window == NULL) {
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error", "Could not create window: %s", mainSystems.window);

		return false;
	}

	mainSystems.glContext = SDL_GL_CreateContext(mainSystems.window);

	if (mainSystems.glContext == NULL) {
		SDL_Log("Cound not create context: %s", SDL_GetError());

		return -1;
	}

	printf("Initialization of OpenGL has begun\n");

	glewExperimental = 1;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		printf("Error: %s\n", glewGetErrorString(err));
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Error", "Not possible to start GLEW", mainSystems.window);
		return false;
	}
	else {
		printf("GLEW successfully initialized\n");
	}

	printf("\nOpenGL version: %s\n", glGetString(GL_VERSION));
	printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer device: %s\n\n", glGetString(GL_RENDERER));

	glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, &total_mem_kb);

	printf("Total video memory: %d MB\n\n", total_mem_kb / 1000);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(0);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void cleanUp(void) {
	SDL_GL_DeleteContext(mainSystems.glContext);
	SDL_DestroyWindow(mainSystems.window);
	SDL_Quit();
}