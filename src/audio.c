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

static int newSound() {
	int i = 0;

	for ( i = 0; i < state->soundCount; i++ ) {
		if ( state->sounds[i] == NULL ) {
			break;
		}
	}
	state->sounds[i] = malloc( sizeof( Sound ) );
	checkSoundRealloc( i );

	return i;
}

static int newWave() {
	int i = 0;

	for ( i = 0; i < state->waveCount; i++ ) {
		if ( state->waves[i] == NULL ) {
			break;
		}
	}
	state->waves[i] = malloc( sizeof( Wave ) );
	checkWaveRealloc( i );

	return i;
}

/*
## Audio - Audio device management
*/

/*
> success = RL.SetMasterVolume( float volume )

Set master volume ( listener )

- Failure return false
- Success return true
*/
int laudioSetMasterVolume( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetMasterVolume( float volume )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float volume = lua_tonumber( L, 1 );

	SetMasterVolume( volume );
	lua_pushboolean( L, true );

	return 1;
}

/*
## Audio - Wave/Sound Loading
*/

/*
> sound = RL.LoadSound( string fileName )

Load sound from file

- Failure return -1
- Success return int
*/
int laudioLoadSound( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadSound( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}

	if ( FileExists( lua_tostring( L, 1 ) ) ) {
		int i = newSound();
		*state->sounds[i] = LoadSound( lua_tostring( L, 1 ) );
		lua_pushinteger( L, i );
		return 1;
	}
	else {
		lua_pushinteger( L, -1 );
		return 1;
	}
}

/*
> wave = RL.LoadWave( string fileName )

Load wave data from file

- Failure return -1
- Success return int
*/
int laudioLoadWave( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadWave( string fileName )" );
		lua_pushinteger( L, -1 );
		return 1;
	}

	if ( FileExists( lua_tostring( L, 1 ) ) ) {
		int i = newWave();
		*state->waves[i] = LoadWave( lua_tostring( L, 1 ) );
		lua_pushinteger( L, i );
		return 1;
	}
	else {
		lua_pushinteger( L, -1 );
		return 1;
	}
}

/*
> sound = RL.LoadSoundFromWave( Wave wave )

Load sound from wave data

- Failure return -1
- Success return int
*/
int laudioLoadSoundFromWave( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadSoundFromWave( Wave wave )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t waveId = lua_tointeger( L, 1 );

	if ( !validWave( waveId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = newSound();
	*state->sounds[i] = LoadSoundFromWave( *state->waves[ waveId ] );
	lua_pushinteger( L, i );

	return 1;
}

/*
> success = RL.UnloadSound( Sound sound )

Unload sound

- Failure return false
- Success return true
*/
int laudioUnloadSound( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.UnloadSound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadSound( *state->sounds[ soundId ] );
	state->sounds[ soundId ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.UnloadWave( Wave wave )

Unload wave data

- Failure return false
- Success return true
*/
int laudioUnloadWave( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.UnloadWave( Wave wave )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t waveId = lua_tointeger( L, 1 );

	if ( !validWave( waveId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	UnloadWave( *state->waves[ waveId ] );
	state->waves[ waveId ] = NULL;
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ExportWave( Wave wave, string fileName )

Export wave data to file, returns true on success

- Failure return false
- Success return true
*/
int laudioExportWave( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ExportWave( Wave wave, string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t waveId = lua_tointeger( L, 1 );

	if ( !validWave( waveId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushboolean( L, ExportWave( *state->waves[ waveId ], lua_tostring( L, 2 ) ) );

	return 1;
}

/*
> success = RL.ExportWaveAsCode( Wave wave, string fileName )

Export wave sample data to code (.h), returns true on success

- Failure return false
- Success return true
*/
int laudioExportWaveAsCode( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isstring( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ExportWaveAsCode( Wave wave, string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t waveId = lua_tointeger( L, 1 );

	if ( !validWave( waveId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	lua_pushboolean( L, ExportWaveAsCode( *state->waves[ waveId ], lua_tostring( L, 2 ) ) );

	return 1;
}

/*
## Audio - Wave/Sound management
*/

/*
> success = RL.PlaySound( Sound sound )

Play a sound

- Failure return false
- Success return true
*/
int laudioPlaySound( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.PlaySound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	PlaySound( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.StopSound( Sound sound )

Stop playing a sound

- Failure return false
- Success return true
*/
int laudioStopSound( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.StopSound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	StopSound( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.PauseSound( Sound sound )

Pause a sound

- Failure return false
- Success return true
*/
int laudioPauseSound( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.PauseSound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	PauseSound( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.ResumeSound( Sound sound )

Resume a paused sound

- Failure return false
- Success return true
*/
int laudioResumeSound( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.ResumeSound( Sound sound )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	ResumeSound( *state->sounds[ soundId ] );
	lua_pushboolean( L, true );

	return 1;
}

/*
> playing = RL.IsSoundPlaying( Sound sound )

Check if a sound is currently playing

- Failure return nil
- Success return bool
*/
int laudioIsSoundPlaying( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.IsSoundPlaying( Sound sound )" );
		lua_pushnil( L );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );

	if ( !validSound( soundId ) ) {
		lua_pushnil( L );
		return 1;
	}
	lua_pushboolean( L, IsSoundPlaying( *state->sounds[ soundId ] ) );

	return 1;
}

/*
> success = RL.SetSoundVolume( Sound sound, float volume )

Set volume for a sound ( 1.0 is max level )

- Failure return false
- Success return true
*/
int laudioSetSoundVolume( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetSoundVolume( Sound sound, float volume )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );
	float volume = lua_tonumber( L, 2 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetSoundVolume( *state->sounds[ soundId ], volume );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetSoundPitch( Sound sound, float pitch )

Set pitch for a sound ( 1.0 is base level )

- Failure return false
- Success return true
*/
int laudioSetSoundPitch( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetSoundPitch( Sound sound, float pitch )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );
	float pitch = lua_tonumber( L, 2 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetSoundPitch( *state->sounds[ soundId ], pitch );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetSoundPan( Sound sound, float pan )

Set pan for a sound ( 0.5 is center )

- Failure return false
- Success return true
*/
int laudioSetSoundPan( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetSoundPan( Sound sound, float pitch )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t soundId = lua_tointeger( L, 1 );
	float pan = lua_tonumber( L, 2 );

	if ( !validSound( soundId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	SetSoundPan( *state->sounds[ soundId ], pan );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )

Convert wave data to desired format

- Failure return false
- Success return true
*/
int laudioWaveFormat( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) || !lua_isnumber( L, 4 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t waveId = lua_tointeger( L, 1 );
	int sampleRate = lua_tointeger( L, 2 );
	int sampleSize = lua_tointeger( L, 3 );
	int channels = lua_tointeger( L, 4 );

	if ( !validWave( waveId ) ) {
		lua_pushboolean( L, false );
		return 1;
	}
	WaveFormat( state->waves[ waveId ], sampleRate, sampleSize, channels );
	lua_pushboolean( L, true );

	return 1;
}

/*
> wave = RL.WaveCopy( Wave wave )

Copy a wave to a new wave

- Failure return -1
- Success return int
*/
int laudioWaveCopy( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.WaveCopy( Wave wave )" );
		lua_pushinteger( L, -1 );
		return 1;
	}
	size_t waveId = lua_tointeger( L, 1 );

	if ( !validWave( waveId ) ) {
		lua_pushinteger( L, -1 );
		return 1;
	}
	int i = newWave();
	*state->waves[i] = WaveCopy( *state->waves[ waveId ] );
	lua_pushinteger( L, i );

	return 1;
}

/*
> success = RL.WaveCrop( Wave wave, int initSample, int finalSample )

Crop a wave to defined samples range

- Failure return false
- Success return true
*/
int laudioWaveCrop( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) || !lua_isnumber( L, 2 ) || !lua_isnumber( L, 3 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.WaveCrop( Wave wave, int initSample, int finalSample )" );
		lua_pushboolean( L, false );
		return 1;
	}
	size_t waveId = lua_tointeger( L, 1 );
	int initSample = lua_tointeger( L, 2 );
	int finalSample = lua_tointeger( L, 3 );

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
> success = RL.LoadMusicStream( string fileName )

Load music stream from file

- Failure return false
- Success return true
*/
int laudioLoadMusicStream( lua_State *L ) {
	if ( !lua_isstring( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.LoadMusicStream( string fileName )" );
		lua_pushboolean( L, false );
		return 1;
	}
	if ( FileExists( lua_tostring( L, 1 ) ) ) {
		state->music = LoadMusicStream( lua_tostring( L, 1 ) );
		state->music.looping = false;
		
		lua_pushboolean( L, true );
	}
	else {
		lua_pushboolean( L, false );
	}

	return 1;
}

/*
> RL.PlayMusicStream()

Start music playing
*/
int laudioPlayMusicStream( lua_State *L ) {
	PlayMusicStream( state->music );

	return 0;
}

/*
> playing = RL.IsMusicStreamPlaying()

Check if music is playing

- Success return bool
*/
int laudioIsMusicStreamPlaying( lua_State *L ) {
	lua_pushboolean( L, IsMusicStreamPlaying( state->music ) );

	return 1;
}

/*
> RL.StopMusicStream()

Stop music playing
*/
int laudioStopMusicStream( lua_State *L ) {
	StopMusicStream( state->music );

	return 0;
}

/*
> RL.PauseMusicStream()

Pause music playing
*/
int laudioPauseMusicStream( lua_State *L ) {
	PauseMusicStream( state->music );

	return 0;
}

/*
> RL.ResumeMusicStream()

Resume playing paused music
*/
int laudioResumeMusicStream( lua_State *L ) {
	ResumeMusicStream( state->music );

	return 0;
}

/*
> success = RL.SeekMusicStream( float position )

Seek music to a position ( in seconds )

- Failure return false
- Success return true
*/
int laudioSeekMusicStream( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SeekMusicStream( float position )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float position = lua_tonumber( L, 1 );

	SeekMusicStream( state->music, position );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetMusicVolume( float volume )

Set volume for music ( 1.0 is max level )

- Failure return false
- Success return true
*/
int laudioSetMusicVolume( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetMusicVolume( float volume )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float volume = lua_tonumber( L, 1 );

	SetMusicVolume( state->music, volume );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetMusicPitch( float pitch )

Set pitch for a music ( 1.0 is base level )

- Failure return false
- Success return true
*/
int laudioSetMusicPitch( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetMusicPitch( float pitch )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float pitch = lua_tonumber( L, 1 );

	SetMusicPitch( state->music, pitch );
	lua_pushboolean( L, true );

	return 1;
}

/*
> success = RL.SetMusicPan( float pan )

Set pan for a music ( 0.5 is center )

- Failure return false
- Success return true
*/
int laudioSetMusicPan( lua_State *L ) {
	if ( !lua_isnumber( L, 1 ) ) {
		TraceLog( LOG_WARNING, "%s", "Bad call of function. RL.SetMusicPan( float pan )" );
		lua_pushboolean( L, false );
		return 1;
	}
	float pan = lua_tonumber( L, 1 );

	SetMusicPitch( state->music, pan );
	lua_pushboolean( L, true );

	return 1;
}

/*
> length = RL.GetMusicTimeLength()

Get music time length ( in seconds )

- Success return float
*/
int laudioGetMusicTimeLength( lua_State *L ) {
	lua_pushnumber( L, GetMusicTimeLength( state->music ) );

	return 1;
}

/*
> played = RL.GetMusicTimePlayed()

Get current music time played ( in seconds )

- Success return float
*/
int laudioGetMusicTimePlayed( lua_State *L ) {
	lua_pushnumber( L, GetMusicTimePlayed( state->music ) );

	return 1;
}
