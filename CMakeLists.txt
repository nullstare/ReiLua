cmake_minimum_required( VERSION 3.15 )
project( ReiLua )

# find_package( raylib 3.7 REQUIRED ) # Requires at least version 3.7

set( CMAKE_C_STANDARD 11 ) # Requires C11 standard

if( UNIX )
	set( CMAKE_C_COMPILER "gcc" )
elseif( APPLE )
	set( CMAKE_C_COMPILER "clang" )
endif()

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb -std=c11 -Wall -pedantic -fno-common" )
# set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -std=c11 -Wall -pedantic -fno-common" )

option( STATIC ON )
option( DRM OFF )

include_directories( include )
file( GLOB SOURCES "src/*.c" )
add_executable( ${PROJECT_NAME} ${SOURCES} )

if( STATIC )
	message( Static )
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libraylib.a )
	target_link_libraries( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/liblua.a )
else()
	find_package( raylib 4.0 REQUIRED ) # Requires at least version 4.0
	message( Shared )
	target_link_libraries( ${PROJECT_NAME} raylib )
	target_link_libraries( ${PROJECT_NAME} lua )
endif()

if( UNIX )
	if( DRM ) # Raspberry pi
		# target_link_libraries( ${PROJECT_NAME} GLESv2 EGL drm gbm rt bcm_host m dl pthread )
		target_link_libraries( ${PROJECT_NAME} GLESv2 EGL drm gbm rt m dl pthread )
	else()
		target_link_libraries( ${PROJECT_NAME} m dl pthread )
	endif()
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if( APPLE )
    target_link_libraries( ${PROJECT_NAME} "-framework IOKit" )
    target_link_libraries( ${PROJECT_NAME} "-framework Cocoa" )
    target_link_libraries( ${PROJECT_NAME} "-framework OpenGL" )
endif()
