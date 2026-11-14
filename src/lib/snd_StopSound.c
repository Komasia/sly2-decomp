// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// name: Sly 1 989snd.c: command 0x15, 4 bytes, no wait
void snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(int, int, void *, int, int);
void snd_StopSound(int a) { int buf[1]; buf[0] = a; snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(0x15, 4, buf, 0, 0); }
