#include "main.h"
#include "state.h"
#include "audio.h"
#include "lua_core.h"

static bool validSound( size_t id ) {
	if ( id < 0 || state->soundCount < id || state->sounds[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid sound", id );
		return false;
	}
	else {
		return true;
	}
}

static void checkSoundRealloc( int i ) {
	if ( i == state->soundCount ) {
		state->soundCount++;
	}

	if ( state->soundCount == state->soundAlloc ) {
		state->soundAlloc += ALLOC_PAGE_SIZE;
		state->sounds = realloc( state->sounds, state->soundAlloc * sizeof( Sound* ) );

		for ( i = state->soundCount; i < state->soundAlloc; i++ ) {
			state->sounds[i] = NULL;
		}
	}
}

/*
## Audio - Sounds
*/

/*
> sound = RL_LoadSound( string fileName )

Load sound from file

- Failure return -1
- Success return int
*/
int laudioLoadSound( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadSound( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}

	if ( FileExists( lua_tostring( L, -1 ) ) ) {
		int i = 0;

		for ( i = 0; i < state->soundCount; i++ ) {
			if ( state->sounds[i] == NULL ) {
				break;
			}
		}
		state->sounds[i] = malloc( sizeof( Sound ) );
		*state->sounds[i] = LoadSound( lua_tostring( L, -1 ) );
		lua_pushinteger( L, i );
		checkSoundRealloc( i );
	}

	return 1;
}

/*
> success = RL_PlaySoundMulti( Sound sound )

Play a sound ( Using multichannel buffer pool )

- Failure return false
- Success return true
*/
int laudioPlaySoundMulti( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_PlaySoundMulti( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	if ( !validSound( lua_tointeger( L, -1 ) ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	PlaySoundMulti( *state->sounds[ lua_tointeger( L, -1 ) ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetSoundVolume( Sound sound, float volume )

Set volume for a sound ( 1.0 is max level )

- Failure return false
- Success return true
*/
int laudioSetSoundVolume( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetSoundVolume( Sound sound, float volume )" );
		lua_pushboolean( L, false );
		return 1;
	}
	if ( !validSound( lua_tointeger( L, -2 ) ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetSoundVolume( *state->sounds[ lua_tointeger( L, -2 ) ], lua_tonumber( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_SetSoundPitch( Sound sound, float pitch )

Set pitch for a sound ( 1.0 is base level )

- Failure return false
- Success return true
*/
int laudioSetSoundPitch( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetSoundPitch( Sound sound, float pitch )" );
		lua_pushboolean( L, false );
		return 1;
	}
	if ( !validSound( lua_tointeger( L, -2 ) ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetSoundPitch( *state->sounds[ lua_tointeger( L, -2 ) ], lua_tonumber( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_UnloadSound( Sound sound )

Unload sound

- Failure return false
- Success return true
*/
int laudioUnloadSound( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadSound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

	if ( !validSound( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadSound( *state->sounds[ id ] );
	state->sounds[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
## Audio - Music
*/

/*
> success = RL_LoadMusicStream( string fileName )

Load music stream from file

- Failure return false
- Success return true
*/
int laudioLoadMusicStream( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadMusicStream( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	if ( FileExists( lua_tostring( L, -1 ) ) ) {
		state->music = LoadMusicStream( lua_tostring( L, -1 ) );
		state->music.looping = false;
		
		lua_pushboolean( L, true );
	}
	else {
		lua_pushboolean( L, false );
	}

	return 1;
}

/*
> PlayMusicStream()

Start music playing
*/
int laudioPlayMusicStream( lua_State *L ) {
	PlayMusicStream( state->music );

	return 1;
}

/*
> StopMusicStream()

Stop music playing
*/
int laudioStopMusicStream( lua_State *L ) {
	StopMusicStream( state->music );

	return 1;
}

/*
> PauseMusicStream()

Pause music playing
*/
int laudioPauseMusicStream( lua_State *L ) {
	PauseMusicStream( state->music );

	return 1;
}

/*
> ResumeMusicStream()

Resume playing paused music
*/
int laudioResumeMusicStream( lua_State *L ) {
	ResumeMusicStream( state->music );

	return 1;
}

/*
> playing = PlayMusicStream()

Check if music is playing

- Success return bool
*/
int laudioIsMusicStreamPlaying( lua_State *L ) {
	lua_pushboolean( L, IsMusicStreamPlaying( state->music ) );

	return 1;
}

/*
> success = RL_SetMusicVolume( float volume )

Set volume for music ( 1.0 is max level )

- Failure return false
- Success return true
*/
int laudioSetMusicVolume( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetMusicVolume( float volume )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetMusicVolume( state->music, lua_tonumber( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}
