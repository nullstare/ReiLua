#pragma once

#ifdef PLATFORM_DESKTOP_SDL
	#define PLATFORM_SDL_EVENT_QUEUE_LEN 128
#endif

typedef struct {
	char *exePath;
	bool hasWindow;
	bool run;
	bool gcUnload;
	lua_State *luaState;
	Vector2 resolution;
	int logLevelInvalid;
	Font defaultFont;
	Material defaultMaterial;
	int *RLGLcurrentShaderLocs;
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
#elif PLATFORM_DESKTOP_SDL
	int SDL_eventQueueLen;
	SDL_Event *SDL_eventQueue;
#endif
} State;

extern State *state;

bool stateInit( int argn, const char **argc, const char *exePath );
void stateInitInterpret( int argn, const char **argc );
void stateFree();
