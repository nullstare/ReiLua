cmake_minimum_required( VERSION 3.9 )
project( ReiLua )

set( CMAKE_C_STANDARD 99 ) # Requires C99 standard

if( UNIX )
	set( CMAKE_C_COMPILER "gcc" )
elseif( APPLE )
	set( CMAKE_C_COMPILER "clang" )
# elseif( WIN32 )
# 	set( CMAKE_C_COMPILER "mingw32" )
endif()

# set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb -std=c99 -Wall -pedantic -fno-common" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -std=c99 -Wall -pedantic -fno-common" )

include_directories( include )
file( GLOB SOURCES "src/*.c" )
add_executable( ${PROJECT_NAME} ${SOURCES} )

if( SHARED )
	message( Shared )
	find_package( raylib 4.0 REQUIRED ) # Requires at least version 4.0
	target_link_libraries( ${PROJECT_NAME} raylib )
	target_link_libraries( ${PROJECT_NAME} lua )
else()
	message( Static )
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libraylib.a )
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/liblua.a )
	# target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libluajit.a )
endif()

if( UNIX )
	if( DRM ) # Mainly for Raspberry pi
		# target_link_libraries( ${PROJECT_NAME} GLESv2 EGL drm gbm rt bcm_host m dl pthread )
		target_link_libraries( ${PROJECT_NAME} GLESv2 EGL drm gbm rt m dl pthread )
	else()
		target_link_libraries( ${PROJECT_NAME} m dl pthread )
	endif()
endif()

if( WIN32 )
	target_link_libraries( ${PROJECT_NAME} mingw32 opengl32 gdi32 winmm )
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if( APPLE )
    target_link_libraries( ${PROJECT_NAME} "-framework IOKit" )
    target_link_libraries( ${PROJECT_NAME} "-framework Cocoa" )
    target_link_libraries( ${PROJECT_NAME} "-framework OpenGL" )
endif()
