set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
include( CMakeDependentOption )
include( EnumOption )

cmake_minimum_required( VERSION 3.9 )
project( ReiLua )

# To make web build
# cmake .. -DCMAKE_TOOLCHAIN_FILE=<YOUR PATH HERE>/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM=Web

set( CMAKE_C_STANDARD 99 ) # Requires C99 standard

option( SHARED "Build using dynamic libraries." off )
option( LUAJIT "Use LuaJIT." off )
option( LUA_EVENTS "Enable Lua event callbacks (RL.event)." off )

enum_option( PLATFORM "Desktop;Desktop_SDL;Web" "Platform to build for." )

if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES )
	set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
	set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo" )
endif()

file( GLOB SOURCES src/*.c )

include_directories( include )
add_executable( ${PROJECT_NAME} ${SOURCES} )

if( PLATFORM STREQUAL "Desktop" )
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPLATFORM_DESKTOP" )
elseif( PLATFORM STREQUAL "Desktop_SDL" )
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPLATFORM_DESKTOP_SDL" )
elseif( PLATFORM STREQUAL "Web" )
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPLATFORM_WEB" )
endif()

if( LUA_EVENTS )
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLUA_EVENTS" )
endif()

if( PLATFORM STREQUAL "Web" )
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/web/libraylib.a )
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/web/liblua.a )

	# Try "-s USE_PTHREADS" if not getting pixel perfect rendering.
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY" )
	# set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s FORCE_FILESYSTEM=1" )
	set( CMAKE_EXECUTABLE_SUFFIX ".html" ) # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
	set( resources_dir "resources@/" ) # Sets resources as root for the virtual file system.
	set_target_properties( ${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${resources_dir}" )
else() # Desktop
	if( SHARED )
		message( Shared )
		set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSHARED" )
		# find_package( raylib 5.0 REQUIRED ) # Requires at least version 5.0
		target_link_libraries( ${PROJECT_NAME} raylib )

		if( LUAJIT )
			target_link_libraries( ${PROJECT_NAME} luajit )
		else()
			target_link_libraries( ${PROJECT_NAME} lua )
		endif()
	else()
		message( Static )
		target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libraylib.a )

		if( LUAJIT )
			set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLUAJIT" )
			target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libluajit.a )
		else()
			target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/liblua.a )
		endif()
	endif()

	if( UNIX )
		set( CMAKE_C_COMPILER "gcc" )

		if ( PLATFORM MATCHES "Desktop_SDL" )
			include( FindPkgConfig )
			pkg_search_module( SDL2 REQUIRED sdl2 )
			include_directories( ${SDL2_INCLUDE_DIRS} )
			target_link_libraries( ${PROJECT_NAME} ${SDL2_LIBRARIES} )
		endif()

		if( DRM ) # For Raspberry Pi
			# target_link_libraries( ${PROJECT_NAME} GLESv2 EGL drm gbm rt bcm_host m dl pthread )
			# target_link_libraries( ${PROJECT_NAME} GLESv2 EGL drm gbm pthread rt m dl )
			target_link_libraries( ${PROJECT_NAME} raylib GLESv2 EGL pthread rt m gbm drm dl atomic )
		else()
			target_link_libraries( ${PROJECT_NAME} m dl pthread )
		endif()
	elseif( APPLE )
		set( CMAKE_C_COMPILER "clang" )

		# TODO Linking to sdl2.

		target_link_libraries( ${PROJECT_NAME} "-framework IOKit" )
		target_link_libraries( ${PROJECT_NAME} "-framework Cocoa" )
		target_link_libraries( ${PROJECT_NAME} "-framework OpenGL" )
	elseif( WIN32 )
		if ( PLATFORM MATCHES "Desktop_SDL" )
			find_package( SDL2 REQUIRED )
			include_directories( ${SDL2_INCLUDE_DIRS} )
			target_link_libraries( ${PROJECT_NAME} ${SDL2MAIN_LIBRARIES} )
			target_link_libraries( ${PROJECT_NAME} ${SDL2_LIBRARIES} )
		endif()
		# Remove this to get console.
		set( CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-mwindows" )
		target_link_libraries( ${PROJECT_NAME} mingw32 opengl32 gdi32 winmm )
	endif()
endif()
