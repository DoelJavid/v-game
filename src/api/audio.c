/**
  src/api/audio.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "audio.h"

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
generate_waveform(short* buffer, int samples, waveform_params_t params) {
  float wave_step = ROOT_NOTE_FREQUENCY *
                    powf(2.0f, (float)params.semitone / 12.0f) / SAMPLE_RATE;
  float wave_index = 0.0f;

  for (int i = 0; i < samples; i++) {
    float sample = step_oscillator(params.type, wave_index);
    sample *= params.volume;
    buffer[i] = (short)(sample * 32767.0f);

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
  short buffer[total_samples];
  generate_waveform(buffer, total_samples, params);

  // clang-format off
  Wave sound_wave = (Wave){
    .frameCount = total_samples,
    .sampleRate = SAMPLE_RATE,
    .sampleSize = 16,
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
  for (int i = 0; i < sizeof(channels) / sizeof(Sound); i++) {
    if (IsSoundValid(channels[i])) {
      // Unload the sound and assign it to NULL to ensure this resource is
      // never freed again.
      UnloadSound(channels[i]);
      channels[i] = (Sound){0};
    }
  }

  if (IsAudioDeviceReady())
    CloseAudioDevice();
}
