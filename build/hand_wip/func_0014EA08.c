/* 7 diffs: target hoists the 0x40 constant (0x40 - c) into $fp and spills pgMax to the stack; ours keeps pgMax in $fp. */
typedef int qword __attribute__((mode(TI)));
struct T { int a, b, c; };
struct O { char pad[0x70]; int c; struct T *at; };
struct HIT { char pad[0x40]; float g40; float g44; char pad2[0x18]; };
int func_00118668(struct T *pBegin, struct T *pEnd, qword pos, qword dir, int c, struct HIT *ahit);
int func_0014C9F8(int c, struct HIT *ahit, int cNew, struct HIT *ahitNew, int cMax, struct HIT *ahitOut, int f);
int func_0014EA08(int n, struct O **apo, qword pos, qword dir, float g, float *pgMin, float *pgMax)
{
    struct HIT ahit[0x40];
    int c = 0;
    int i;
    int j;
    float g0, g1;
    for (i = 0; i < n; i++) {
        struct O *po = apo[i];
        int cNew = func_00118668(po->at, po->at + po->c, pos, dir, 0x40 - c, &ahit[c]);
        if (cNew)
            c = func_0014C9F8(c, ahit, cNew, &ahit[c], 0x40, ahit, 0);
    }
    for (j = 0; ; j++) {
        if (c < j)
            return 0;
        g0 = 0.0f;
        if (j > 0)
            g0 = ahit[j - 1].g44;
        if (j < c)
            g1 = ahit[j].g40;
        else
            g1 = 1.0f;
        if (g < g1 - g0)
            break;
    }
    if (pgMin)
        *pgMin = g0;
    if (pgMax)
        *pgMax = g1;
    return 1;
}
