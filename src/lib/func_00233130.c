// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* 989snd: send command 0x68: a 16-byte header (a, b, c, d) plus c bytes of data, with a completion callback. */
void snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(int, int, void *, int, int);
void func_00233130(int a, int b, int c, int d, int e, int f) { int buf[4]; buf[0] = a; buf[1] = b; buf[2] = c; buf[3] = d; snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(0x68, c + 0xC, buf, e, f); }
