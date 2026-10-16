// WIP (Claude agent): all-volatile globals give target's program-order and nop jal slots. Only remaining diff: target 'lui s0,%hi(D_002C67A0)' directly, ours 'lui a0' + 'daddu s0,a0' (gcse reaching-reg copy; same issue as InitTimer/_lf_bind).
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
extern volatile int D_002C67A0;
extern volatile int D_002C67A4;
extern volatile int D_002C6774;
extern volatile int D_002C6768;
extern volatile int D_002C6754;
extern volatile int D_002C6760;
extern volatile int D_004502C0;
int func_00234A50(int);
void func_002418D0(int *data)
{
    D_002C67A0 = *data;
    D_002C67A4 = D_002C67A0;
    if (D_002C67A0 == 11) {
        D_002C67A0 = 0;
        D_002C6774 = 0;
        return;
    }
    func_00234A50(D_002C6768);
    if (D_002C6754 != 0 && D_004502C0 != 0)
        func_00234A50(D_002C6760);
    else
        D_002C6774 = 0;
    D_002C67A0 = 0;
}
