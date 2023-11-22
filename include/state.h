#pragma once

#define ALLOC_PAGE_SIZE 256

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
	/* GLFW events. */
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
// #elif PLATFORM_DESKTOP_SDL

#endif
} State;

extern State *state;

bool stateInit( int argn, const char **argc, const char *exePath );
void stateInitInterpret( int argn, const char **argc );
void stateFree();
