#pragma once

#ifdef PLATFORM_DESKTOP_SDL
	#define PLATFORM_SDL_EVENT_QUEUE_LEN 128
#endif

typedef struct {
	char* basePath;
	bool hasWindow;
	bool run;
	bool gcUnload;
	int lineSpacing; /* We need to store copy here since raylib has it in static. */
	Vector2 mouseOffset;
	Vector2 mouseScale;
	lua_State* luaState;
	Vector2 resolution;
	int logLevelInvalid;
	Font defaultFont;
	Font guiDefaultFont;
	Material defaultMaterial;
	Texture defaultTexture;
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
#elif PLATFORM_DESKTOP_SDL
	int SDL_eventQueueLen;
	SDL_Event* SDL_eventQueue;
#endif
} State;

extern State* state;

bool stateInit( int argn, const char** argc, const char* basePath );
void stateInitInterpret( int argn, const char** argc );
void stateFree();
