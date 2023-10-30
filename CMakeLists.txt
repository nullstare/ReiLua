cmake_minimum_required( VERSION 3.9 )
project( ReiLua )

# To make web build
# cmake .. -DCMAKE_TOOLCHAIN_FILE=<YOUR PATH HERE>/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM=Web

set( CMAKE_C_STANDARD 99 ) # Requires C99 standard

option( SHARED "Build using dynamic libraries." off )
option( LUAJIT "Use LuaJIT." off )
option( GC_UNLOAD "Lua garbage collector unloads objects. If off, object unloading should be handled manually." on )

if( NOT CMAKE_BUILD_TYPE )
  	SET( CMAKE_BUILD_TYPE Release CACHE STRING
      	"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      	FORCE )
endif()

if( GC_UNLOAD )
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGC_UNLOAD" )
endif()

file( GLOB SOURCES src/*.c )

include_directories( include )
add_executable( ${PROJECT_NAME} ${SOURCES} )

if( EMSCRIPTEN ) # Web
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/web/libraylib.a )
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/web/liblua.a )

	# Try "-s USE_PTHREADS" if not getting pixel perfect rendering.
	set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY" )
  	set( CMAKE_EXECUTABLE_SUFFIX ".html" ) # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
	set( resources_dir "resources" )
	set_target_properties( ${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${resources_dir}" )
else() # Desktop
	if( SHARED )
		message( Shared )
		set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSHARED" )
		find_package( raylib 4.5 REQUIRED ) # Requires at least version 4.5
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

		if( DRM ) # Mainly for Raspberry Pi
			# target_link_libraries( ${PROJECT_NAME} GLESv2 EGL drm gbm rt bcm_host m dl pthread )
			# target_link_libraries( ${PROJECT_NAME} GLESv2 EGL drm gbm pthread rt m dl )
			target_link_libraries( ${PROJECT_NAME} raylib GLESv2 EGL pthread rt m gbm drm dl atomic )
		else()
			target_link_libraries( ${PROJECT_NAME} m dl pthread )
		endif()
	elseif( APPLE )
		set( CMAKE_C_COMPILER "clang" )

		target_link_libraries( ${PROJECT_NAME} "-framework IOKit" )
		target_link_libraries( ${PROJECT_NAME} "-framework Cocoa" )
		target_link_libraries( ${PROJECT_NAME} "-framework OpenGL" )
	elseif( WIN32 )
		# Remove this to get console.
		set( CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-mwindows" )
		target_link_libraries( ${PROJECT_NAME} mingw32 opengl32 gdi32 winmm )
	endif()
endif()
