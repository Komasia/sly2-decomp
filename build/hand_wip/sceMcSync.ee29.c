// (Claude agent, -Os sweep) 16 diffs with -Os (was 49 at -O2)
// (Claude agent) near miss: logic+slti right; reg alloc differs (target lui s3 for D_002C8350 hi, s2=mode,s4=cmd,s5=result)
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -Os -G0
// SLY2_ASM: gnu-reorder-db
extern int D_002C8350;
extern int D_002C8354;
extern int D_002C8358;
extern int D_00451E40;
int func_00234A70(int);
int func_00234A60(int);
int func_00234A40(int);
int sceMcSync(int mode, int *cmd, int *result)
{
    int r;
    if (!D_002C8350) return -1;
    if (func_00234A70(D_002C8358) < 0) r = 1; else r = 0;
    if (mode == 0 && r) {
        func_00234A60(D_002C8358);
        r = 0;
    }
    r = !r;
    if (cmd) *cmd = D_002C8350;
    if (r) {
        D_002C8350 = 0;
        if (result) *result = D_00451E40;
        func_00234A40(D_002C8354);
    }
    return r;
}
