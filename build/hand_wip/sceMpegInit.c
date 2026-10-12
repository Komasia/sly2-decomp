// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
int func_00239450(void);
int func_002394A0(void);
void sceIpuInit(void);
#define REG(a) (*(volatile unsigned int *)(a))
int sceMpegInit(void)
{
  int s = func_00239450();
  REG(0x1000F590) = REG(0x1000F520) | 0x10000;
  REG(0x1000B000) = REG(0x1000B000) & ~0x100;
  REG(0x1000B400) = REG(0x1000B400) & ~0x100;
  REG(0x1000F590) = REG(0x1000F520) & ~0x10000;
  if (s) func_002394A0();
  REG(0x1000B020) = 0;
  REG(0x1000B420) = 0;
  sceIpuInit();
  return 1;
}
