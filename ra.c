// audio stuff | dep free
#include <stddef.h>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

// others
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  ma_engine en;
  ma_result en_init_result = ma_engine_init(NULL, &en); // engine init
  if (en_init_result != MA_SUCCESS) {
    printf(
        "gg something went wrong while trying to initialize the audio engine");
    return 1;
  }

  struct dirent *dir;
  int cap = 20;
  int count = 0;
  char **bs = malloc(cap * sizeof(char *)); // to store pointers to strings

  // main loop
  int sel = 0;
  while (1) {
    // TODO: random selection logic
    DIR *d = opendir(".");
    if (!d) {
      printf("gg something went wrong while tring to open current working "
             "directory");
      return 1;
    }

    while ((dir = readdir(d)) != NULL) {
      if (strstr(dir->d_name, ".mp3")) {
        bs[count] = strdup(dir->d_name);
        count++;
      }
    }

    ma_result rr = ma_engine_play_sound(&en, bs[sel], NULL);
    if (rr != MA_SUCCESS)
      printf("gg playback error: %d\n", rr);

    for (int i = 0; i < count; i++) {
      free(bs[i]);
    }
    closedir(d);

    count = 0;
    getchar();
  }
}
