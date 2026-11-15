// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// name: Sly 1 989snd.c snd_InitMovieSound: command 0x3B, waited (Sly 2 sends 6 ints / 0x18 bytes where Sly 1 sends 5); next to snd_ResetMovieSound / CloseMovieSound / StartMovieSound (0x3D / 0x3C / 0x3E)
int snd_SendIOPCommandAndWait__FiiPc(int, int, void *);
int snd_InitMovieSound(int sizeOfIOPBuffer, int volumeLevel, int panCenter, int volumeGroup, int type, int f) { int buf[6]; buf[0] = sizeOfIOPBuffer; buf[1] = volumeLevel; buf[2] = panCenter; buf[3] = volumeGroup; buf[4] = type; buf[5] = f; return snd_SendIOPCommandAndWait__FiiPc(0x3B, 0x18, buf); }
