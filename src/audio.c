#include "main.h"
#include "state.h"
#include "audio.h"
#include "lua_core.h"

/*
## Audio - Audio device management functions
*/

/*
> RL.InitAudioDevice()

Initialize audio device and context
*/
int laudioInitAudioDevice( lua_State *L ) {
	InitAudioDevice();

	return 0;
}

/*
> RL.CloseAudioDevice()

Close the audio device and context
*/
int laudioCloseAudioDevice( lua_State *L ) {
	CloseAudioDevice();

	return 0;
}

/*
> isReady = RL.IsAudioDeviceReady()

Check if audio device has been initialized successfully

- Success return bool
*/
int laudioIsAudioDeviceReady( lua_State *L ) {
	lua_pushboolean( L, IsAudioDeviceReady() );

	return 1;
}

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
> isReady = RL.GetMasterVolume()

Get master volume (listener)

- Success return float
*/
int laudioGetMasterVolume( lua_State *L ) {
	lua_pushnumber( L, GetMasterVolume() );

	return 1;
}

/*
## Audio - Wave/Sound loading/unloading functions
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
> isReady = RL.IsWaveReady( Wave wave )

Checks if wave data is ready

- Success return bool
*/
int laudioIsWaveReady( lua_State *L ) {
	Wave *wave = uluaGetWave( L, 1 );

	lua_pushboolean( L, IsWaveReady( *wave ) );

	return 1;
}

/*
> sound = RL.LoadSoundFromWave( Wave wave )

Load sound from wave data

- Success return Sound
*/
int laudioLoadSoundFromWave( lua_State *L ) {
	Wave *wave = uluaGetWave( L, 1 );

	uluaPushSound( L, LoadSoundFromWave( *wave ) );

	return 1;
}

/*
> sound = RL.LoadSoundAlias( Sound source )

Create a new sound that shares the same sample data as the source sound, does not own the sound data

- Success return Sound
*/
int laudioLoadSoundAlias( lua_State *L ) {
	Sound *source = uluaGetSound( L, 1 );

	uluaPushSound( L, LoadSoundAlias( *source ) );

	return 1;
}

/*
> isReady = RL.IsSoundReady( Sound sound )

Checks if a sound is ready

- Success return bool
*/
int laudioIsSoundReady( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );

	lua_pushboolean( L, IsSoundReady( *sound ) );

	return 1;
}

/*
> RL.UnloadWave( Wave wave )

Unload wave data
*/
int laudioUnloadWave( lua_State *L ) {
	Wave *wave = uluaGetWave( L, 1 );

	UnloadWave( *wave );

	return 0;
}

/*
> RL.UnloadSound( Sound sound )

Unload sound
*/
int laudioUnloadSound( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );

	UnloadSound( *sound );

	return 0;
}

/*
> RL.UnloadSoundAlias( Sound alias )

Unload a sound alias (does not deallocate sample data)
*/
int laudioUnloadSoundAlias( lua_State *L ) {
	Sound *alias = uluaGetSound( L, 1 );

	UnloadSoundAlias( *alias );

	return 0;
}

/*
> success = RL.ExportWave( Wave wave, string fileName )

Export wave data to file, returns true on success

- Success return bool
*/
int laudioExportWave( lua_State *L ) {
	Wave *wave = uluaGetWave( L, 1 );

	lua_pushboolean( L, ExportWave( *wave, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
> success = RL.ExportWaveAsCode( Wave wave, string fileName )

Export wave sample data to code (.h), returns true on success

- Success return true
*/
int laudioExportWaveAsCode( lua_State *L ) {
	Wave *wave = uluaGetWave( L, 1 );

	lua_pushboolean( L, ExportWaveAsCode( *wave, luaL_checkstring( L, 2 ) ) );

	return 1;
}

/*
## Audio - Wave/Sound management functions
*/

/*
> RL.PlaySound( Sound sound )

Play a sound
*/
int laudioPlaySound( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );

	PlaySound( *sound );

	return 0;
}

/*
> RL.StopSound( Sound sound )

Stop playing a sound
*/
int laudioStopSound( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );

	StopSound( *sound );

	return 0;
}

/*
> RL.PauseSound( Sound sound )

Pause a sound
*/
int laudioPauseSound( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );

	PauseSound( *sound );

	return 0;
}

/*
> RL.ResumeSound( Sound sound )

Resume a paused sound
*/
int laudioResumeSound( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );

	ResumeSound( *sound );

	return 0;
}

/*
> playing = RL.IsSoundPlaying( Sound sound )

Check if a sound is currently playing

- Success return bool
*/
int laudioIsSoundPlaying( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );

	lua_pushboolean( L, IsSoundPlaying( *sound ) );

	return 1;
}

/*
> RL.SetSoundVolume( Sound sound, float volume )

Set volume for a sound (1.0 is max level)
*/
int laudioSetSoundVolume( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );
	float volume = luaL_checknumber( L, 2 );

	SetSoundVolume( *sound, volume );

	return 0;
}

/*
> RL.SetSoundPitch( Sound sound, float pitch )

Set pitch for a sound (1.0 is base level)
*/
int laudioSetSoundPitch( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );
	float pitch = luaL_checknumber( L, 2 );

	SetSoundPitch( *sound, pitch );

	return 0;
}

/*
> RL.SetSoundPan( Sound sound, float pan )

Set pan for a sound (0.5 is center)
*/
int laudioSetSoundPan( lua_State *L ) {
	Sound *sound = uluaGetSound( L, 1 );
	float pan = luaL_checknumber( L, 2 );

	SetSoundPan( *sound, pan );

	return 0;
}

/*
> RL.WaveFormat( Wave wave, int sampleRate, int sampleSize, int channels )

Convert wave data to desired format
*/
int laudioWaveFormat( lua_State *L ) {
	Wave *wave = uluaGetWave( L, 1 );
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
	Wave *wave = uluaGetWave( L, 1 );

	uluaPushWave( L, WaveCopy( *wave ) );

	return 1;
}

/*
> RL.WaveCrop( Wave wave, int initSample, int finalSample )

Crop a wave to defined samples range
*/
int laudioWaveCrop( lua_State *L ) {
	Wave *wave = uluaGetWave( L, 1 );
	int initSample = luaL_checkinteger( L, 2 );
	int finalSample = luaL_checkinteger( L, 3 );

	WaveCrop( wave, initSample, finalSample );

	return 0;
}

/*
## Audio - Music management functions
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
> isReady = RL.IsMusicReady( Music music )

Checks if a music stream is ready

- Success return bool
*/
int laudioIsMusicReady( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	lua_pushboolean( L, IsMusicReady( *music ) );

	return 1;
}

/*
> RL.UnloadMusicStream( Music music )

Unload music stream
*/
int laudioUnloadMusicStream( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	UnloadMusicStream( *music );

	return 0;
}

/*
> RL.PlayMusicStream( Music music )

Start music playing
*/
int laudioPlayMusicStream( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	PlayMusicStream( *music );

	return 0;
}

/*
> playing = RL.IsMusicStreamPlaying( Music music )

Check if music is playing

- Success return bool
*/
int laudioIsMusicStreamPlaying( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	lua_pushboolean( L, IsMusicStreamPlaying( *music ) );

	return 1;
}

/*
> RL.UpdateMusicStream( Music music )

Updates buffers for music streaming
*/
int laudioUpdateMusicStream( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	UpdateMusicStream( *music );

	return 0;
}

/*
> RL.StopMusicStream( Music music )

Stop music playing
*/
int laudioStopMusicStream( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	StopMusicStream( *music );

	return 0;
}

/*
> RL.PauseMusicStream( Music music )

Pause music playing
*/
int laudioPauseMusicStream( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	PauseMusicStream( *music );

	return 0;
}

/*
> RL.ResumeMusicStream( Music music )

Resume playing paused music
*/
int laudioResumeMusicStream( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	ResumeMusicStream( *music );

	return 0;
}

/*
> RL.SeekMusicStream( Music music, float position )

Seek music to a position (in seconds)
*/
int laudioSeekMusicStream( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );
	float position = luaL_checknumber( L, 2 );

	SeekMusicStream( *music, position );

	return 0;
}

/*
> RL.SetMusicVolume( Music music, float volume )

Set volume for music (1.0 is max level)
*/
int laudioSetMusicVolume( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );
	float volume = luaL_checknumber( L, 2 );

	SetMusicVolume( *music, volume );

	return 0;
}

/*
> RL.SetMusicPitch( Music music, float pitch )

Set pitch for a music (1.0 is base level)
*/
int laudioSetMusicPitch( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );
	float pitch = luaL_checknumber( L, 2 );

	SetMusicPitch( *music, pitch );

	return 0;
}

/*
> RL.SetMusicPan( Music music, float pan )

Set pan for a music (0.5 is center)
*/
int laudioSetMusicPan( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );
	float pan = luaL_checknumber( L, 2 );

	SetMusicPitch( *music, pan );

	return 0;
}

/*
> RL.SetMusicLooping( Music music, bool looping )

Set looping for a music
*/
int laudioSetMusicLooping( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );
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
	Music *music = uluaGetMusic( L, 1 );

	lua_pushboolean( L, music->looping );

	return 1;
}

/*
> length = RL.GetMusicTimeLength( Music music )

Get music time length (in seconds)

- Success return float
*/
int laudioGetMusicTimeLength( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	lua_pushnumber( L, GetMusicTimeLength( *music ) );

	return 1;
}

/*
> timePlayed = RL.GetMusicTimePlayed( Music music )

Get current music time played (in seconds)

- Success return float
*/
int laudioGetMusicTimePlayed( lua_State *L ) {
	Music *music = uluaGetMusic( L, 1 );

	lua_pushnumber( L, GetMusicTimePlayed( *music ) );

	return 1;
}
