#pragma once

#define STRING_LEN 1024

#define VERSION_MAJOR 0
#define VERSION_MINOR 5
#define VERSION_PATCH 0
#define VERSION_DEV 1

#include "glad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#include "glfw3.h"
#include "glfw3native.h"
#include <stdint.h>

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
