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

static bool validWave( size_t id ) {
	if ( id < 0 || state->waveCount < id || state->waves[ id ] == NULL ) {
		TraceLog( LOG_WARNING, "%s %d", "Invalid wave", id );
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

static void checkWaveRealloc( int i ) {
	if ( i == state->waveCount ) {
		state->waveCount++;
	}

	if ( state->waveCount == state->waveAlloc ) {
		state->waveAlloc += ALLOC_PAGE_SIZE;
		state->waves = realloc( state->waves, state->waveAlloc * sizeof( Wave* ) );

		for ( i = state->waveCount; i < state->waveAlloc; i++ ) {
			state->waves[i] = NULL;
		}
	}
}

/*
## Audio - Audio device management
*/

/*
> success = RL_SetMasterVolume( float volume )

Set master volume ( listener )

- Failure return false
- Success return true
*/
int laudioSetMasterVolume( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetMasterVolume( float volume )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetMasterVolume( lua_tonumber( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Audio - Wave/Sound Loading
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
	else {
		lua_pushinteger( L, -1 );
	}

	return 1;
}

/*
> wave = RL_LoadWave( string fileName )

Load wave data from file

- Failure return -1
- Success return int
*/
int laudioLoadWave( lua_State *L ) {
	if ( !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadWave( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}

	if ( FileExists( lua_tostring( L, -1 ) ) ) {
		int i = 0;

		for ( i = 0; i < state->waveCount; i++ ) {
			if ( state->waves[i] == NULL ) {
				break;
			}
		}
		state->waves[i] = malloc( sizeof( Wave ) );
		*state->waves[i] = LoadWave( lua_tostring( L, -1 ) );
		lua_pushinteger( L, i );
		checkWaveRealloc( i );
	}
	else {
		lua_pushinteger( L, -1 );
	}
	return 1;
}

/*
> sound = RL_LoadSoundFromWave( Wave wave )

Load sound from wave data

- Failure return -1
- Success return int
*/
int laudioLoadSoundFromWave( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_LoadSoundFromWave( Wave wave )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t waveId = lua_tointeger( L, -1 );

	if ( !validWave( waveId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = 0;

	for ( i = 0; i < state->soundCount; i++ ) {
		if ( state->sounds[i] == NULL ) {
			break;
		}
	}
	state->sounds[i] = malloc( sizeof( Sound ) );
	*state->sounds[i] = LoadSoundFromWave( *state->waves[ waveId ] );
	lua_pushinteger( L, i );
	checkSoundRealloc( i );

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
> success = RL_UnloadWave( Wave wave )

Unload wave data

- Failure return false
- Success return true
*/
int laudioUnloadWave( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_UnloadWave( Wave wave )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -1 );

	if ( !validWave( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadWave( *state->waves[ id ] );
	state->waves[ id ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_ExportWave( Wave wave, string fileName )

Export wave data to file, returns true on success

- Failure return false
- Success return true
*/
int laudioExportWave( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ExportWave( Wave wave, string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -2 );

	if ( !validWave( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushboolean( L, ExportWave( *state->waves[ id ], lua_tostring( L, -1 ) ) );

	return 1;
}

/*
> success = RL_ExportWaveAsCode( Wave wave, string fileName )

Export wave sample data to code (.h), returns true on success

- Failure return false
- Success return true
*/
int laudioExportWaveAsCode( lua_State *L ) {
	if ( !lua_isnumber( L, -2 ) || !lua_isstring( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ExportWaveAsCode( Wave wave, string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t id = lua_tointeger( L, -2 );

	if ( !validWave( id ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushboolean( L, ExportWaveAsCode( *state->waves[ id ], lua_tostring( L, -1 ) ) );

	return 1;
}

/*
## Audio - Wave/Sound management
*/

/*
> success = RL_PlaySound( Sound sound )

Play a sound

- Failure return false
- Success return true
*/
int laudioPlaySound( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_PlaySound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, -1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	PlaySound( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_StopSound( Sound sound )

Stop playing a sound

- Failure return false
- Success return true
*/
int laudioStopSound( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_StopSound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, -1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	StopSound( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_PauseSound( Sound sound )

Pause a sound

- Failure return false
- Success return true
*/
int laudioPauseSound( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_PauseSound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, -1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	PauseSound( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL_ResumeSound( Sound sound )

Resume a paused sound

- Failure return false
- Success return true
*/
int laudioResumeSound( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_ResumeSound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, -1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ResumeSound( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

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
	size_t soundId = lua_tointeger( L, -1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	PlaySoundMulti( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> RL_StopSoundMulti()

Stop any sound playing ( using multichannel buffer pool )
*/
int laudioStopSoundMulti( lua_State *L ) {
	StopSoundMulti();

	return 0;
}

/*
> count = RL_GetSoundsPlaying()

Get number of sounds playing in the multichannel

- Success return int
*/
int laudioGetSoundsPlaying( lua_State *L ) {
	lua_pushinteger( L, GetSoundsPlaying() );

	return 1;
}

/*
> playing = RL_IsSoundPlaying( Sound sound )

Check if a sound is currently playing

- Failure return nil
- Success return bool
*/
int laudioIsSoundPlaying( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_IsSoundPlaying( Sound sound )" );
		lua_pushnil( L );
		return 1;
	}
	size_t soundId = lua_tointeger( L, -1 );

	if ( !validSound( soundId ) ) {
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsSoundPlaying( *state->sounds[ soundId ] ) );

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
> success = RL_WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )

Convert wave data to desired format

- Failure return false
- Success return true
*/
int laudioWaveFormat( lua_State *L ) {
	if ( !lua_isnumber( L, -4 ) || !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int channels = lua_tointeger( L, -1 );
	int sampleSize = lua_tointeger( L, -2 );
	int sampleRate = lua_tointeger( L, -3 );
	size_t waveId = lua_tointeger( L, -4 );

	if ( !validWave( waveId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	WaveFormat( state->waves[ waveId ], sampleRate, sampleSize, channels );
	lua_pushboolean( L, true );

	return 1;
}

/*
> wave = RL_WaveCopy( Wave wave )

Copy a wave to a new wave

- Failure return -1
- Success return int
*/
int laudioWaveCopy( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_WaveCopy( Wave wave )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t waveId = lua_tointeger( L, -1 );

	if ( !validWave( waveId ) ) {
		lua_pushnil( L );
		return 1;
	}
	int i = 0;

	for ( i = 0; i < state->waveCount; i++ ) {
		if ( state->waves[i] == NULL ) {
			break;
		}
	}
	state->waves[i] = malloc( sizeof( Wave ) );
	*state->waves[i] = WaveCopy( *state->waves[ waveId ] );
	lua_pushinteger( L, i );
	checkWaveRealloc( i );

	return 1;
}

/*
> success = RL_WaveCrop( Wave wave, int initSample, int finalSample )

Crop a wave to defined samples range

- Failure return false
- Success return true
*/
int laudioWaveCrop( lua_State *L ) {
	if ( !lua_isnumber( L, -3 ) || !lua_isnumber( L, -2 ) || !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_WaveCrop( Wave wave, int initSample, int finalSample )" );
		lua_pushboolean( L, false );
		return 1;
	}
	int finalSample = lua_tointeger( L, -1 );
	int initSample = lua_tointeger( L, -2 );
	size_t waveId = lua_tointeger( L, -3 );

	if ( !validWave( waveId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	WaveCrop( state->waves[ waveId ], initSample, finalSample );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Audio - Music management
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
> RL_PlayMusicStream()

Start music playing
*/
int laudioPlayMusicStream( lua_State *L ) {
	PlayMusicStream( state->music );

	return 0;
}

/*
> playing = RL_PlayMusicStream()

Check if music is playing

- Success return bool
*/
int laudioIsMusicStreamPlaying( lua_State *L ) {
	lua_pushboolean( L, IsMusicStreamPlaying( state->music ) );

	return 1;
}

/*
> RL_StopMusicStream()

Stop music playing
*/
int laudioStopMusicStream( lua_State *L ) {
	StopMusicStream( state->music );

	return 0;
}

/*
> RL_PauseMusicStream()

Pause music playing
*/
int laudioPauseMusicStream( lua_State *L ) {
	PauseMusicStream( state->music );

	return 0;
}

/*
> RL_ResumeMusicStream()

Resume playing paused music
*/
int laudioResumeMusicStream( lua_State *L ) {
	ResumeMusicStream( state->music );

	return 0;
}

/*
> success = RL_SeekMusicStream( float position )

Seek music to a position ( in seconds )

- Failure return false
- Success return true
*/
int laudioSeekMusicStream( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SeekMusicStream( float position )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SeekMusicStream( state->music, lua_tonumber( L, -1 ) );
	lua_pushboolean( L, true );

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

/*
> success = RL_SetMusicPitch( float pitch )

Set pitch for a music ( 1.0 is base level )

- Failure return false
- Success return true
*/
int laudioSetMusicPitch( lua_State *L ) {
	if ( !lua_isnumber( L, -1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL_SetMusicPitch( float pitch )" );
		lua_pushboolean( L, false );
		return 1;
	}
	SetMusicPitch( state->music, lua_tonumber( L, -1 ) );
	lua_pushboolean( L, true );

	return 1;
}

/*
> length = RL_GetMusicTimeLength()

Get music time length ( in seconds )

- Success return float
*/
int laudioGetMusicTimeLength( lua_State *L ) {
	lua_pushnumber( L, GetMusicTimeLength( state->music ) );

	return 1;
}

/*
> played = RL_GetMusicTimePlayed()

Get current music time played ( in seconds )

- Success return float
*/
int laudioGetMusicTimePlayed( lua_State *L ) {
	lua_pushnumber( L, GetMusicTimePlayed( state->music ) );

	return 1;
}
