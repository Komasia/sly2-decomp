// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder
// 4/13 with gnu-reorder: the `sw $zero,D_002C4A7C` is scheduled last (into the jal slot); target issues it right after `sd ra`.
// Scheduler difference (all 2.95 builds, -mcpu=*, sched flags, volatile, 2.96 tried). Same as sceSifLoadFileReset.
extern int D_002C4A7C; extern char D_00447DA8[];
void *func_002333B4(void *p, int c, unsigned int n);
int sceFsReset(void)
{
    D_002C4A7C = 0;
    func_002333B4(D_00447DA8, 0, 4);
    return 0;
}
