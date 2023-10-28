#pragma once

#define ALLOC_PAGE_SIZE 256

typedef struct {
	ModelAnimation *animations;
	unsigned int animCount;
} ModelAnimations;

typedef struct {
	char *exePath;
	bool hasWindow;
	bool run;
	lua_State *luaState;
	Vector2 resolution;
	int logLevelInvalid;
	/* Resources. */
		/* Meshes. */
	Mesh **meshes;
	size_t meshCount;
	size_t meshAlloc;
		/* Materials. */
	Material **materials;
	size_t materialCount;
	size_t materialAlloc;
		/* Models. */
	Model **models;
	size_t modelCount;
	size_t modelAlloc;
		/* ModelAnimations. */
	ModelAnimations **animations;
	size_t animationCount;
	size_t animationAlloc;
	/* Raylib GLFW input callback events. */
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
} State;

extern State *state;

bool stateInit( int argn, const char **argc, const char *exePath );
void stateInitInterpret( int argn, const char **argc );
void stateFree();
