struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct E { int k; int pad; float g8; };
struct O { char pad[0xF80]; int nF80; char pad2[0xFD0 - 0xF84]; char aFD0[4]; };
struct S { char pad[0x10]; struct O *p10; int pad2; void *p18; char pad3[0x1C]; struct E *pe; float g3C; int n40; int pad4; float g48; };
int FDone__11JOBPATHSTEP(void *p);
int func_0017CE30(void *p);
int func_0017D188(void *p);
int NArrived__7JOBGOTO(void *p);
int func_00174FB8(void *p);
void SetMoveHeading__FP7MOVEREF(void *p, float g);
void func_001EF0D8(void *p);
// name: SafeHouse port (JOBSCRIPT::FRunning)
int FRunning__9JOBSCRIPT(struct S *p) {
    if (!p->n40) return 0;
    switch (p->pe->k) {
    case 6:
        switch (p->p10->nF80) {
        case -1:
            if (FDone__11JOBPATHSTEP(p->p18)) p->n40 = 0;
            break;
        case 0:
            if (func_0017CE30(p->p18)) p->n40 = 0;
            break;
        case 1:
            if (func_0017D188(p->p18)) p->n40 = 0;
            break;
        }
        break;
    case 7:
        if (NArrived__7JOBGOTO(p->p18)) {
            p->n40 = 0;
            SetMoveHeading__FP7MOVEREF(p->p10->aFD0, p->g48);
        }
        break;
    case 5:
        if (p->pe->g8 < g_clock.t - p->g3C) p->n40 = 0;
        break;
    case 13: case 14:
        if (func_00174FB8(p->p18)) p->n40 = 0;
        break;
    }
    if (!p->n40) func_001EF0D8(&p->p18);
    return p->n40;
}
