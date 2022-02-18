#pragma once

/* Sounds. */
int laudioLoadSound( lua_State *L );
int laudioPlaySoundMulti( lua_State *L );
int laudioSetSoundVolume( lua_State *L );
int laudioSetSoundPitch( lua_State *L );
int laudioUnloadSound( lua_State *L );
/* Music. */
int laudioLoadMusicStream( lua_State *L );
int laudioPlayMusicStream( lua_State *L );
int laudioStopMusicStream( lua_State *L );
int laudioPauseMusicStream( lua_State *L );
int laudioResumeMusicStream( lua_State *L );
int laudioIsMusicStreamPlaying( lua_State *L );
int laudioSetMusicVolume( lua_State *L );
