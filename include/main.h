#pragma once

#define STRING_LEN 1024

#define VERSION_MAJOR 0
#define VERSION_MINOR 9
#define VERSION_PATCH 0
#define VERSION_DEV 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "external/glad.h"
#include "external/stb_rect_pack.h"

#ifdef PLATFORM_DESKTOP
	#include "GLFW/glfw3.h"
	#include "GLFW/glfw3native.h"
#elif PLATFORM_DESKTOP_SDL2
	#include <SDL2/SDL.h>
#elif PLATFORM_DESKTOP_SDL3
	#include <SDL3/SDL.h>
#endif

#ifdef SHARED
	#include <raylib.h>
	#include <rlgl.h>
	#include <raymath.h>
	#include <raygui.h>
	#include <rlights.h>
	#include <rcamera.h>
#else
	#include "raylib.h"
	#include "rlgl.h"
	#include "raymath.h"
	#include "raygui.h"
	#include "rlights.h"
	#include "rcamera.h"
#endif

#ifdef LUAJIT
	#ifdef SHARED
		#include <lua.h>
		#include <luajit.h>
		#include <lualib.h>
		#include <lauxlib.h>
	#else
		#include "luajit/lua.h"
		#include "luajit/luajit.h"
		#include "luajit/lualib.h"
		#include "luajit/lauxlib.h"
	#endif
#else
	#ifdef SHARED
		#include <lua.h>
		#include <lualib.h>
		#include <lauxlib.h>
	#else
		#include "lua/lua.h"
		#include "lua/lualib.h"
		#include "lua/lauxlib.h"
	#endif
#endif
