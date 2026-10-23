// audio stuff | dep free
#include <stddef.h>
#define MA_NO_FLAC
#define MA_NO_VORBIS
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

// others
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

unsigned int rng(unsigned int min, unsigned int max) {
  return min + (rand() % (max - min + 1));
}

int main() {
  // init
  ma_engine en;
  ma_result en_init_result = ma_engine_init(NULL, &en); // engine init
  if (en_init_result != MA_SUCCESS) {
    printf(RED "gg something went wrong while trying to initialize the audio "
               "engine" RESET);
    return 1;
  }

  struct dirent *dir;
  int cap = 20;
  int count = 0;
  char **bs = malloc(cap * sizeof(char *)); // to store pointers to strings

  srand((unsigned int)time((NULL))); // seed

  // range input
  int max, min;
  printf(BLUE "Enter " RED "min " BLUE "and " RED "max " BLUE
              "wait time in seconds (min max): " RESET);
  scanf("%d %d", &min, &max);

  // main loop
  while (1) {
    DIR *d = opendir(".");
    if (!d) {
      printf(RED "gg something went wrong while tring to open current working "
                 "directory" RESET);
      return 1;
    }

    while ((dir = readdir(d)) != NULL) {
      if (strstr(dir->d_name, ".mp3")) {
        if (count >= cap) {
          cap += 10;
          bs = realloc(bs, cap * sizeof(char *));
        }
        bs[count] = strdup(dir->d_name);
        count++;
      }
    }

    int sel = rng(0, count - 1);
    int fun = rng(1, 5);

    // increasing amplitude? whatever
    printf(GREEN "Playing: %s X %d\n", bs[sel], fun);
    for (int i = 0; i < fun; i++) {
      ma_result rr = ma_engine_play_sound(&en, bs[sel], NULL);
      if (rr != MA_SUCCESS)
        printf(RED "gg playback error: " RESET "%d\n", rr);
    }

    for (int i = 0; i < count; i++) {
      free(bs[i]);
    }
    closedir(d);

    count = 0;
    sleep(rng(min, max));
  }
}
