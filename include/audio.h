#pragma once

/* Audio device management functions. */
int laudioInitAudioDevice( lua_State* L );
int laudioCloseAudioDevice( lua_State* L );
int laudioIsAudioDeviceReady( lua_State* L );
int laudioSetMasterVolume( lua_State* L );
int laudioGetMasterVolume( lua_State* L );
/* Wave/Sound loading/unloading functions. */
int laudioLoadSound( lua_State* L );
int laudioLoadWave( lua_State* L );
int laudioLoadWaveFromMemory( lua_State* L );
int laudioIsWaveReady( lua_State* L );
int laudioLoadSoundFromWave( lua_State* L );
int laudioLoadSoundAlias( lua_State* L );
int laudioIsSoundReady( lua_State* L );
int laudioUnloadWave( lua_State* L );
int laudioUnloadSound( lua_State* L );
int laudioUnloadSoundAlias( lua_State* L );
int laudioExportWave( lua_State* L );
int laudioExportWaveAsCode( lua_State* L );
/* Wave/Sound management functions. */
int laudioPlaySound( lua_State* L );
int laudioStopSound( lua_State* L );
int laudioPauseSound( lua_State* L );
int laudioResumeSound( lua_State* L );
int laudioIsSoundPlaying( lua_State* L );
int laudioSetSoundVolume( lua_State* L );
int laudioSetSoundPitch( lua_State* L );
int laudioSetSoundPan( lua_State* L );
int laudioWaveFormat( lua_State* L );
int laudioWaveCopy( lua_State* L );
int laudioWaveCrop( lua_State* L );
/* Music management functions. */
int laudioLoadMusicStream( lua_State* L );
int laudioLoadMusicStreamFromMemory( lua_State* L );
int laudioIsMusicReady( lua_State* L );
int laudioUnloadMusicStream( lua_State* L );
int laudioPlayMusicStream( lua_State* L );
int laudioIsMusicStreamPlaying( lua_State* L );
int laudioUpdateMusicStream( lua_State* L );
int laudioStopMusicStream( lua_State* L );
int laudioPauseMusicStream( lua_State* L );
int laudioResumeMusicStream( lua_State* L );
int laudioSeekMusicStream( lua_State* L );
int laudioSetMusicVolume( lua_State* L );
int laudioSetMusicPitch( lua_State* L );
int laudioSetMusicPan( lua_State* L );
int laudioSetMusicLooping( lua_State* L );
int laudioGetMusicLooping( lua_State* L );
int laudioGetMusicTimeLength( lua_State* L );
int laudioGetMusicTimePlayed( lua_State* L );
