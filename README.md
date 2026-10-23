'TODO: maybe a gui(?) and better terminal output'

# random-audio
A small C program to play random local audio files at a random time

## Why?
Rather than searching for videos on youtube for "1Hr of silence occasionally broken by...", just run this program to enjoy uninterrupted custom jumpscares
(you can set the random range to whatever you like ;) )

## Build
I made this to be dependency free (except maybe miniaudio BUT WHATEVER) because i don't want to clutter for a program i designed to be as small and self contained as possible. For it only supports linux.

### Linux:
```fish
gcc ./ra.c -o ./ra -lm -lpthread
```

## How to use it?
<p>
After compiling and getting the executable, place it either inside the folder which houses your audio files or add the location of the executable to PATH.<br>
Run the executable and enter the limits for the random play time in seconds in the format `x y` after when the prompt asks. For now, only integers are accepted. But i will change it to float later<br>
</p>

## Funnies
The function that plays the audio is non blocking, so if it were to happen the random chosen wait time for the next audio is close to 0, it WILL overlap. This adds it's own funny factor.<br><br>

Since the audio playing function is non blocking and you get the freedom to set the limits to whatever you desire... well, I'll leave that for you to find out xd.
