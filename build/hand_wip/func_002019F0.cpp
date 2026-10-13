typedef unsigned long ulong;
struct SBE { int cb; char *pv; };
extern "C" void *func_002333B4(void *, int, int);
struct SPRBUF {
    ulong *aqw; char *pv; SBE a[8]; int c; int state;
    SPRBUF() { func_002333B4(this, 0, sizeof(*this)); }
};
struct SLOTHEAP { int a[10]; };
extern SPRBUF D_003DD2C0[2];
extern char D_003DD380[], D_003DD400[];
extern int D_002DD2E0, D_002DD2E4, D_002DD2E8, D_002DD2EC, D_002DD2F0, D_002DD2F4;
extern SLOTHEAP D_004520A8, D_004520D0, D_004520F8, D_00452120, D_00452148, D_00452170;
extern "C" void func_0011CCA8(SLOTHEAP *, int, int, int);
extern "C" void func_002019F0(int init, int priority)
{
    if (priority == 0xFFFF && init) {
        { SPRBUF b;
          b.pv = (char *)0x70000000;
          b.aqw = (ulong *)((int)D_003DD380 | 0x20000000);
          D_003DD2C0[0] = b;
        }
        { SPRBUF b;
          b.aqw = (ulong *)((int)D_003DD400 | 0x20000000);
          b.pv = (char *)0x70002000;
          D_003DD2C0[1] = b;
        }
        if (++D_002DD2E0 == 1) func_0011CCA8(&D_004520A8, 0x14, 0x2000, 0x10);
        if (++D_002DD2E4 == 1) func_0011CCA8(&D_004520D0, 0x18, 0x800, 0x10);
        if (++D_002DD2E8 == 1) func_0011CCA8(&D_004520F8, 0x28, 0x200, 0x10);
        if (++D_002DD2EC == 1) func_0011CCA8(&D_00452120, 0x1C, 0x800, 0x10);
        if (++D_002DD2F0 == 1) func_0011CCA8(&D_00452148, 0xC, 0xC8, 0x10);
        if (++D_002DD2F4 == 1) func_0011CCA8(&D_00452170, 0x14, 0x100, 0x10);
    }
}
