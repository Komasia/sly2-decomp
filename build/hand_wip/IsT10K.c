// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
extern char D_002C8378[]; void GetRomName(char *);
int IsT10K(void) { if (D_002C8378[0] == 0) GetRomName(D_002C8378); return D_002C8378[4] == 0x54; }
