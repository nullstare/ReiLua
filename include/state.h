#pragma once

#if defined PLATFORM_DESKTOP_SDL2 || defined PLATFORM_DESKTOP_SDL3
	#define PLATFORM_SDL_EVENT_QUEUE_LEN 128
#endif

typedef struct {
	char* basePath;
	bool run;
	bool gcUnload;
	int lineSpacing; /* We need to store copy here since raylib has it in static. */
	Vector2 mouseOffset;
	Vector2 mouseScale;
	lua_State* luaState;
	int logLevelInvalid;
	Font defaultFont;
	Font guiFont;
	Material defaultMaterial;
	Texture defaultTexture;
	Texture shapesTexture;
	int* RLGLcurrentShaderLocs;
	/* Events. */
#ifdef PLATFORM_DESKTOP
	/* Window events. */
	GLFWwindowsizefun raylibWindowSizeCallback;
	GLFWwindowmaximizefun raylibWindowMaximizeCallback;
	GLFWwindowiconifyfun raylibWindowIconifyCallback;
	GLFWwindowfocusfun raylibWindowFocusCallback;
	GLFWdropfun raylibWindowDropCallback;
	/* Input events. */
	GLFWkeyfun raylibKeyCallback;
	GLFWcharfun raylibCharCallback;
	GLFWmousebuttonfun raylibMouseButtonCallback;
	GLFWcursorposfun raylibMouseCursorPosCallback;
	GLFWscrollfun raylibMouseScrollCallback;
	GLFWcursorenterfun raylibCursorEnterCallback;
	GLFWjoystickfun raylibJoystickCallback;
	/* NOTE! Experimental. Needs glfw PR https://github.com/glfw/glfw/pull/1445 */
	GLFWpentabletdatafun glfwTabletDataCallback;
	GLFWpentabletcursorfun glfwTabletCursorCallback;
	GLFWpentabletproximityfun glfwTabletProximityCallback;
#elif defined PLATFORM_DESKTOP_SDL2 || defined PLATFORM_DESKTOP_SDL3
	int SDL_eventQueueLen;
	SDL_Event* SDL_eventQueue;
#endif
} State;

extern State* state;

bool stateInit( int argn, const char** argc, const char* basePath );
void stateContextInit();
void stateInitInterpret( int argn, const char** argc );
void stateFree();
