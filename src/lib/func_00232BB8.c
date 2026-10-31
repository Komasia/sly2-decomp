// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
extern int *gSndCommandBuffePtr[]; extern int gCommandFillBuffer; void func_00231C48(void);
void snd_PostMessage__Fv(void) { (*gSndCommandBuffePtr[gCommandFillBuffer])++; func_00231C48(); }
