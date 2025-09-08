/* Based on raylib audio_stream_effects example */

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* gcc audioProcess.c -shared -o audioProcess.so -fPIC -llua */

// Audio effect: lowpass filter
void AudioProcessEffectLPF(void *buffer, unsigned int frames)
{
	static float low[2] = { 0.0f, 0.0f };
	static const float cutoff = 70.0f / 44100.0f; // 70 Hz lowpass filter
	const float k = cutoff / (cutoff + 0.1591549431f); // RC filter formula

	// Converts the buffer data before using it
	float *bufferData = (float *)buffer;
	for (unsigned int i = 0; i < frames*2; i += 2)
	{
		const float l = bufferData[i];
		const float r = bufferData[i + 1];

		low[0] += k * (l - low[0]);
		low[1] += k * (r - low[1]);
		bufferData[i] = low[0];
		bufferData[i + 1] = low[1];
	}
}

static float *delayBuffer = NULL;
static unsigned int delayBufferSize = 0;
static unsigned int delayReadIndex = 2;
static unsigned int delayWriteIndex = 0;

// Audio effect: delay
static void AudioProcessEffectDelay(void *buffer, unsigned int frames)
{
	for (unsigned int i = 0; i < frames*2; i += 2)
	{
		float leftDelay = delayBuffer[delayReadIndex++];    // ERROR: Reading buffer -> WHY??? Maybe thread related???
		float rightDelay = delayBuffer[delayReadIndex++];

		if (delayReadIndex == delayBufferSize) delayReadIndex = 0;

		((float *)buffer)[i] = 0.5f*((float *)buffer)[i] + 0.5f*leftDelay;
		((float *)buffer)[i + 1] = 0.5f*((float *)buffer)[i + 1] + 0.5f*rightDelay;

		delayBuffer[delayWriteIndex++] = ((float *)buffer)[i];
		delayBuffer[delayWriteIndex++] = ((float *)buffer)[i + 1];
		if (delayWriteIndex == delayBufferSize) delayWriteIndex = 0;
	}
}

/* API. */

static int apInit( lua_State* L ) {
	// Allocate buffer for the delay effect
    delayBufferSize = 48000*2;      // 1 second delay (device sampleRate*channels)
    delayBuffer = (float *)calloc(delayBufferSize, sizeof(float));

	return 0;
}

static int getAudioProcessEffectLPF( lua_State* L ) {
	lua_pushlightuserdata( L, AudioProcessEffectLPF );

	return 1;
}

static int getAudioProcessEffectDelay( lua_State* L ) {
	lua_pushlightuserdata( L, AudioProcessEffectDelay );

	return 1;
}

static int apFree( lua_State* L ) {
	free(delayBuffer);       // Free delay buffer

	return 0;
}

static const luaL_Reg audioProcess[] = {
	{ "init", apInit },
	{ "AudioProcessEffectLPF", getAudioProcessEffectLPF },
	{ "AudioProcessEffectDelay", getAudioProcessEffectDelay },
	{ "free", apFree },
	{ NULL, NULL } // sentinel.
};

int luaopen_audioProcess(lua_State *L) {
#if LUA_VERSION_NUM <= 501
	luaL_openlib( L, "audioProcess", audioProcess, 0 );
#else
	luaL_newlib( L, audioProcess );
#endif
	return 1;
}
