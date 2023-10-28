#include "main.h"
#include "state.h"
#include "audio.h"
#include "lua_core.h"

/*
## Audio - Audio device management
*/

/*
> RL.SetMasterVolume( float volume )

Set master volume (listener)
*/
int laudioSetMasterVolume( lua_State *L ) {
	float volume = luaL_checknumber( L, 1 );

	SetMasterVolume( volume );

	return 0;
}

/*
## Audio - Wave/Sound Loading
*/

/*
> sound = RL.LoadSound( string fileName )

Load sound from file

- Failure return nil
- Success return Sound
*/
int laudioLoadSound( lua_State *L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		uluaPushSound( L, LoadSound( lua_tostring( L, 1 ) ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> wave = RL.LoadWave( string fileName )

Load wave data from file

- Failure return nil
- Success return Wave
*/
int laudioLoadWave( lua_State *L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		uluaPushWave( L, LoadWave( lua_tostring( L, 1 ) ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> sound = RL.LoadSoundFromWave( Wave wave )

Load sound from wave data

- Success return Sound
*/
int laudioLoadSoundFromWave( lua_State *L ) {
	Wave *wave = luaL_checkudata( L, 1, "Wave" );

	uluaPushSound( L, LoadSoundFromWave( *wave ) );

	return 1;
}

/*
> success = RL.ExportWave( Wave wave, string fileName )

Export wave data to file, returns true on success

- Success return bool
*/
int laudioExportWave( lua_State *L ) {
	Wave *wave = luaL_checkudata( L, 1, "Wave" );

	lua_pushboolean( L, ExportWave( *wave, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> success = RL.ExportWaveAsCode( Wave wave, string fileName )

Export wave sample data to code (.h), returns true on success

- Success return true
*/
int laudioExportWaveAsCode( lua_State *L ) {
	Wave *wave = luaL_checkudata( L, 1, "Wave" );

	lua_pushboolean( L, ExportWaveAsCode( *wave, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
## Audio - Wave/Sound management
*/

/*
> RL.PlaySound( Sound sound )

Play a sound
*/
int laudioPlaySound( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );

	PlaySound( *sound );

	return 0;
}

/*
> RL.StopSound( Sound sound )

Stop playing a sound
*/
int laudioStopSound( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );

	StopSound( *sound );

	return 0;
}

/*
> RL.PauseSound( Sound sound )

Pause a sound
*/
int laudioPauseSound( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );

	PauseSound( *sound );

	return 0;
}

/*
> RL.ResumeSound( Sound sound )

Resume a paused sound
*/
int laudioResumeSound( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );

	ResumeSound( *sound );

	return 0;
}

/*
> playing = RL.IsSoundPlaying( Sound sound )

Check if a sound is currently playing

- Success return bool
*/
int laudioIsSoundPlaying( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );

	lua_pushboolean( L, IsSoundPlaying( *sound ) );

	return 1;
}

/*
> RL.SetSoundVolume( Sound sound, float volume )

Set volume for a sound (1.0 is max level)
*/
int laudioSetSoundVolume( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );
	float volume = luaL_checknumber( L, 2 );

	SetSoundVolume( *sound, volume );

	return 0;
}

/*
> RL.SetSoundPitch( Sound sound, float pitch )

Set pitch for a sound (1.0 is base level)
*/
int laudioSetSoundPitch( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );
	float pitch = luaL_checknumber( L, 2 );

	SetSoundPitch( *sound, pitch );

	return 0;
}

/*
> RL.SetSoundPan( Sound sound, float pan )

Set pan for a sound (0.5 is center)
*/
int laudioSetSoundPan( lua_State *L ) {
	Sound *sound = luaL_checkudata( L, 1, "Sound" );
	float pan = luaL_checknumber( L, 2 );

	SetSoundPan( *sound, pan );

	return 0;
}

/*
> RL.WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )

Convert wave data to desired format
*/
int laudioWaveFormat( lua_State *L ) {
	Wave *wave = luaL_checkudata( L, 1, "Wave" );
	int sampleRate = luaL_checkinteger( L, 2 );
	int sampleSize = luaL_checkinteger( L, 3 );
	int channels = luaL_checkinteger( L, 4 );

	WaveFormat( wave, sampleRate, sampleSize, channels );

	return 0;
}

/*
> wave = RL.WaveCopy( Wave wave )

Copy a wave to a new wave

- Success return Wave
*/
int laudioWaveCopy( lua_State *L ) {
	Wave *wave = luaL_checkudata( L, 1, "Wave" );

	uluaPushWave( L, WaveCopy( *wave ) );

	return 1;
}

/*
> RL.WaveCrop( Wave wave, int initSample, int finalSample )

Crop a wave to defined samples range
*/
int laudioWaveCrop( lua_State *L ) {
	Wave *wave = luaL_checkudata( L, 1, "Wave" );
	int initSample = luaL_checkinteger( L, 2 );
	int finalSample = luaL_checkinteger( L, 3 );

	WaveCrop( wave, initSample, finalSample );

	return 0;
}

/*
## Audio - Music management
*/

/*
> music = RL.LoadMusicStream( string fileName )

Load music stream from file

- Success return Music
*/
int laudioLoadMusicStream( lua_State *L ) {
	if ( FileExists( luaL_checkstring( L, 1 ) ) ) {
		uluaPushMusic( L, LoadMusicStream( lua_tostring( L, 1 ) ) );

		return 1;
	}
	TraceLog( state->logLevelInvalid, "Invalid file '%s'", lua_tostring( L, 1 ) );
	lua_pushnil( L );

	return 1;
}

/*
> RL.PlayMusicStream( Music music )

Start music playing
*/
int laudioPlayMusicStream( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	PlayMusicStream( *music );

	return 0;
}

/*
> playing = RL.IsMusicStreamPlaying( Music music )

Check if music is playing

- Success return bool
*/
int laudioIsMusicStreamPlaying( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	lua_pushboolean( L, IsMusicStreamPlaying( *music ) );

	return 1;
}

/*
> RL.UpdateMusicStream( Music music )

Updates buffers for music streaming
*/
int laudioUpdateMusicStream( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	UpdateMusicStream( *music );

	return 0;
}

/*
> RL.StopMusicStream( Music music )

Stop music playing
*/
int laudioStopMusicStream( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	StopMusicStream( *music );

	return 0;
}

/*
> RL.PauseMusicStream( Music music )

Pause music playing
*/
int laudioPauseMusicStream( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	PauseMusicStream( *music );

	return 0;
}

/*
> RL.ResumeMusicStream( Music music )

Resume playing paused music
*/
int laudioResumeMusicStream( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	ResumeMusicStream( *music );

	return 0;
}

/*
> RL.SeekMusicStream( Music music, float position )

Seek music to a position (in seconds)
*/
int laudioSeekMusicStream( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );
	float position = luaL_checknumber( L, 2 );

	SeekMusicStream( *music, position );

	return 0;
}

/*
> RL.SetMusicVolume( Music music, float volume )

Set volume for music (1.0 is max level)
*/
int laudioSetMusicVolume( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );
	float volume = luaL_checknumber( L, 2 );

	SetMusicVolume( *music, volume );

	return 0;
}

/*
> RL.SetMusicPitch( Music music, float pitch )

Set pitch for a music (1.0 is base level)
*/
int laudioSetMusicPitch( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );
	float pitch = luaL_checknumber( L, 2 );

	SetMusicPitch( *music, pitch );

	return 0;
}

/*
> RL.SetMusicPan( Music music, float pan )

Set pan for a music (0.5 is center)
*/
int laudioSetMusicPan( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );
	float pan = luaL_checknumber( L, 2 );

	SetMusicPitch( *music, pan );

	return 0;
}

/*
> RL.SetMusicLooping( Music music, bool looping )

Set looping for a music
*/
int laudioSetMusicLooping( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );
	bool looping = uluaGetBoolean( L, 2 );

	music->looping = looping;

	return 0;
}

/*
> looping = RL.GetMusicLooping( Music music )

Get looping of a music

- Success return bool
*/
int laudioGetMusicLooping( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	lua_pushboolean( L, music->looping );

	return 1;
}

/*
> length = RL.GetMusicTimeLength( Music music )

Get music time length (in seconds)

- Success return float
*/
int laudioGetMusicTimeLength( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	lua_pushnumber( L, GetMusicTimeLength( *music ) );

	return 1;
}

/*
> timePlayed = RL.GetMusicTimePlayed( Music music )

Get current music time played (in seconds)

- Success return float
*/
int laudioGetMusicTimePlayed( lua_State *L ) {
	Music *music = luaL_checkudata( L, 1, "Music" );

	lua_pushnumber( L, GetMusicTimePlayed( *music ) );

	return 1;
}
