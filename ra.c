#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <stdio.h>

int main() {
  ma_engine en;
  ma_result en_init_result = ma_engine_init(NULL, &en);
  if (en_init_result != MA_SUCCESS) {
    printf(
        "gg something went wrong while trying to initialize the audio engine");
    return 1;
  }

  while (1) {
    // TODO: random selection logic

    ma_engine_play_sound(&en, "./audio/bark-fart.opus", NULL);
    getchar();
  }
}
