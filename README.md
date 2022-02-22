## About

Idea of this project was to bring the power and simplicity of raylib to easy beginner friendly language like Lua in a very straight forward manner. It is not a straight binding to Raylib, some functions will not be included and some are added. The idea of pointing "main.lua" file and access functions "init", "process" and "draw" are borrowed from Löve game engine.

Need for boilerplate code is minimal and in true Lua fashion (in better and worse) you don't need to worry about types since all Raylib types are just lua tables and object id's. Also what Lua cannot handle, the engine is simple enough to be fairly easily extended with new functionality or by using Lua C-libraries.

ReiLua is not planned to be a one-to-one binding to raylib. If you want more direct bindings, there are other projects like https://github.com/TSnake41/raylib-lua.

Reilua means fair in finnish.

## Status

ReiLua is currently in arbitrary version 0.1 and some planned raylib functionality is still missing but it already has over 300 functions.

List of some missing features that are planned to be included. For specific function check API.

* Core
	* Some screen-space-related functions
	* Files drop
	* custom callbacks
	* camera2d and it's functions
	* VR stereo config functions for VR simulator
* Textures
	* Most image loading functions
	* Image manipulation functions
	* Texture update functions
	* Color/pixel related functions
* Text
	* Some font loading/unloading functions
* Audio
	* Wave
	* AudioStream management functions
* Mesh
	* Some mesh management functions

Submodules.

* Raygui
	* Advanced controls
* Raymath
	* Quaternions
* Physac
	* Whole implementation

## Usage

Application needs 'main.lua' or 'main' file as entry point. ReiLua executable will first look it from same directory. Alternatively, path to the folder where "main.lua" is located can be given as argument. There are three global Lua functions that the engine will call, 'init', 'process' and 'draw'.

Example of basic "main.lua" file that will show basic windows with text.

```
local textColor = BLACK
local textPos = { 192, 200 }

function init()
	RL_SetWindowTitle( "First window" )
end

function process( delta )
	if RL_IsKeyPressed( KEY_ENTER ) then
		textColor = BLUE
		textPos = { 230, 230 }
	end

	if RL_IsKeyPressed( KEY_SPACE ) then
		textColor = BLACK
		textPos = { 192, 200 }
	end
end

function draw()
	RL_ClearBackground( RAYWHITE )
    RL_DrawText( 0, "Congrats! You created your first window!", textPos, 20, 2, textColor )
end
```

Application folder structure should be...

```
GameFolder
 \ReiLua.exe
 \main.lua
```

Application should now start successfully from executable. All functionality can be found in "API".

## Building

I think the simplest way would be to statically link Raylib and Lua to the same executable. Specially on Linux this would simplify distribution of games since different distros tend to use different versions of librarys. Of course if you plan to only experiment with it, this isn't so important. At the time of writing ReiLua uses latest Raylib version from master branch. If you use Raylib v4.0.0 release, you will get a lot of undefined reference errors.

//TODO In future these instructions should be set on fixed release versions of Raylib.

https://github.com/raysan5/raylib

https://github.com/lua/lua

### Linux

Compile Raylib and lua by following their instructions. They will compile to libraylib.a and liblua.a by default.

You need build essential and cmake. If you compiled Raylib you should already have these.

```
sudo apt install build-essential
sudo apt install cmake
```

If compiling statically, move libraylib.a and liblua.a to "ReiLua/lib" folder. From "ReiLua" folder...

```
cd build
cmake ..
make
```

Run example.

```
./ReiLua ../examples/snake/
```

If you now see extremely low res snake racing off the window then you are successfull. Congratulations! You can reset the game by pressing enter.

### Windows

I don't have much experience on compiling on Windows, but I got the following method to work.

* Download "w64devkit" from https://github.com/skeeto/w64devkit and "CMake" from https://cmake.org/download/. Install CMake with path environment variables set.
* Download Raylib source.
* Run "w64devkit.exe" and navigate( ls == dir ) to "raylib-master/src" folder and run...

```
mingw32-make
```

* You should now have "libraylib.a" file in that folder.
* Copy that to "ReiLua/lib" folder.
* I haven't got Lua to compile on Windows so we will download it's binarys from http://luabinaries.sourceforge.net/download.html. Take the one with "Windows x64 DLL and Includes (MingW-w64 6 Built)".
* Copy "liblua54.a" to "ReiLua/lib" folder.
* Change it's name to "liblua.a" or change the part in "CMakeLists.txt" where it links to "/lib/liblua.a" to "/lib/liblua54.a".
* Navigate to "ReiLua/build" folder on "w64devkit" and run...

```
cmake -G "MinGW Makefiles" ..

# Cmake uses NMake Makefiles by default so we will set the Generator to MinGW with -G

mingw32-make
```

* You should now have "ReiLua.exe".
* From Lua folder, copy "lua54.dll" to same folder with "ReiLua.exe". Don't change the name of it!

Run example.

```
./ReiLua.exe ../examples/snake/
```

If you now see extremely low res snake racing off the window then you are successfull. Congratulations! You can reset the game by pressing enter.

### MacOS

Not tested, but I guess it should work similarly to Linux.

### Raspberry Pi

Works best when compiled using PLATFORM=DRM, but Raylib seems to have some problems with the input handling.

### Web

Compile Raylib for web by following it's instructions. https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)#1-install-emscripten-toolchain

Lua can be compiled by making few changes to it's makefile.
```
MYCFLAGS= $(LOCAL) -std=c99 -DLUA_USE_LINUX -DLUA_USE_READLINE
# to
MYCFLAGS= $(LOCAL) -std=c99

MYLIBS= -ldl -lreadline
# to
MYLIBS= -ldl

CC= gcc
# to
CC= emcc

AR= ar rc
# to
AR= emar

# And a little bit more down.
	$(AR) $@ $?
# to
	$(AR) rcs $@ $?
```

* If your enviromental variables for "emsdk" are correct, you should be able to compile with make.
* You should now have "libraylib.a" and "liblua.a" librarys.
* Put them into "ReiLua/lib/web/".
* Navigate into "ReiLua/build/".

Emscripten builds the resources like lua files and images to "ReiLua.data" file so we will create folder called "resources" that should include all that. "resources" should also be included in all resource paths. "main.lua" should be located in the root of that folder. So we should now have.

```
ReiLua
 \build
 |\resources
 ||\main.lua
```

We can now build the game. You can use the command it top of the "CMakeLists.txt" to use emsdk toolchain with cmake. Remember to replace \<YOUR PATH HERE> with correct path.

```
cmake .. -DCMAKE_TOOLCHAIN_FILE=<YOUR PATH HERE>/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM=Web
make
```

You should now have "ReiLua.html", "ReiLua.js", "ReiLua.wasm" and "ReiLua.data". You can test the game by creating localhost with Python.

```
python -m http.server 8080
```

You should now be able to access the webpage from browser.

```
localhost:8080/ReiLua.html
```
