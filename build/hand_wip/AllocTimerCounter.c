// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder
// body matches exactly with gnu-reorder; only the prologue/epilogue differ: target sd s1@0x10,s0@0,ra@0x20 (16-byte slots,
// sd), 2.95.3 gives sq, 2.96 gives 8-byte slots. Blocked like every $s-saving function in the SDK range.
int func_00239450(void);
int func_0023A228(void);
int func_002394A0(void);
int AllocTimerCounter(void)
{
    int st = func_00239450();
    int r = func_0023A228();
    if (st) func_002394A0();
    return r;
}
