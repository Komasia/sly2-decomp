// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
extern struct { char pad[0x10]; int x10; char pad2[0xC]; } D_004505D0[][8];
unsigned char *scePadGetDmaStr(int, int);
int scePadGetState(int port, int slot)
{
  if (*(int *)((char *)D_004505D0 + port * 0x70 + slot * 0x1C + 0x10) == 0) return 0;
  return scePadGetDmaStr(port, slot)[0x71];
}
