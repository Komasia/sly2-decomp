// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
void snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(int, int, void *, int, int);
// name: 989snd snd_StopAllSounds (command 0x18, no data: between ContinueSound 0x14 / PauseAllSoundsInGroup 0x16 family); SafeHouse snd989.h 0x232408
void snd_StopAllSounds(void) { snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(0x18, 0, 0, 0, 0); }
