#ifndef LUALIB_AUDIO_H
#define LUALIB_AUDIO_H

#include <lauxlib.h>
#include <lua.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define ROOT_NOTE_FREQUENCY 440.0f

typedef struct {
  int type, semitone;
  float duration, volume;
} waveform_params_t;

/**
  Initializes audio and all data related to it.

  You must call `audio_free()` before closing the game!
*/
void audio_init(void);

/**
  Plays a given waveform with the given semitone, volume, and duration.
*/
void audio_blip(int waveform_id, int semitone, float volume, float duration);

/**
  Frees all data related to audio.
*/
void audio_free(void);

/**
  Opens the audio library for the given lua state.
*/
void luaopen_audio(lua_State* L);

#endif
