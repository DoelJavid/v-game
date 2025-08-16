#include "audio.h"

// C API

static Sound channels[4] = {};

/**
  Generates a sample of a waveform for the given type.

  Based on this code here:
  https://github.com/mdcrtr/sound-generator/blob/main/src/sound_gen.c
*/
static float step_oscillator(int type, float step) {
  switch (type) {
  case 1: // Square Wave
    return step < 0.5f ? -1.0f : 1.0f;
  case 2: // Triangle Wave
    return step < 0.5f ? 4.0f * step - 1.0f : 1.0f - 4.0f * (step - 0.5f);
  case 3: // Sine Wave
    return sinf(2.0f * PI * step);
  default:
    return sinf(powf(2.0f * PI * step, 3));
  }
}

/**
  Generates a waveform using the given buffer, number of samples, and
  configuration.

  Based on this code here:
  https://github.com/mdcrtr/sound-generator/blob/main/src/sound_gen.c
*/
static void
generate_waveform(char* buffer, int samples, waveform_params_t params) {
  float wave_step = ROOT_NOTE_FREQUENCY *
                    powf(2.0f, (float)params.semitone / 12.0f) / SAMPLE_RATE;
  float wave_index = 0.0f;

  for (int i = 0; i < samples; i++) {
    float sample = step_oscillator(params.type, wave_index);
    sample *= params.volume;
    buffer[i] = (char)(sample * 32767.0f);

    wave_index += wave_step;
    if (wave_index > 1.0f)
      wave_index = 0.0f;

    if (params.type > 3 && i % 64 == 0)
      wave_index = (float)(rand() % 128) / 128;
  }
}

/**
  Generates a raylib sound with the given parameters.
*/
static Sound generate_sound(waveform_params_t params) {
  int total_samples = params.duration * SAMPLE_RATE;
  char buffer[total_samples];
  generate_waveform(buffer, total_samples, params);

  // clang-format off
  Wave sound_wave = (Wave){
    .frameCount = total_samples,
    .sampleRate = SAMPLE_RATE,
    .sampleSize = 8,
    .channels = 1,
    .data = buffer
  };
  // clang-format on

  Sound sound = LoadSoundFromWave(sound_wave);
  return sound;
}

void audio_init(void) {
  InitAudioDevice();

  for (int i = 0; i < sizeof(channels) / sizeof(Sound); i++)
    channels[i] = generate_sound((waveform_params_t){
      .semitone = 3, .type = i + 1, .volume = 1, .duration = 3
    });
}

void audio_blip(int waveform_id, int semitone, float volume, float duration) {
  int channel = waveform_id - 1;

  // clang-format off
  UnloadSound(channels[channel]);
  channels[channel] = generate_sound((waveform_params_t){
    .type = waveform_id,
    .semitone = semitone,
    .volume = volume,
    .duration = duration
  });
  // clang-format on

  PlaySound(channels[channel]);
}

void audio_free(void) {
  for (int i = 0; i < sizeof(channels) / sizeof(Sound); i++)
    UnloadSound(channels[i]);
  CloseAudioDevice();
}

// Lua API

static int luaaudio_blip(lua_State* L) {
  int channel = luaL_checkint(L, 1);

  luaL_checktype(L, 2, LUA_TTABLE);
  lua_getfield(L, 2, "Semitone");
  lua_getfield(L, 2, "Volume");
  lua_getfield(L, 2, "Duration");

  int semitone = luaL_optint(L, -3, 3);
  float volume = luaL_optnumber(L, -2, 0.5f);
  float duration = luaL_optnumber(L, -1, 0.2f);

  lua_pop(L, 3);
  audio_blip(channel, semitone, volume, duration);
  return 0;
}

void luaopen_audio(lua_State* L) {
  // clang-format off
  static const luaL_Reg luaaudio_lib[] = {
    {"blip", luaaudio_blip},
    {NULL, NULL}
  };
  // clang-format on

  luaL_register(L, "audio", luaaudio_lib);
}
