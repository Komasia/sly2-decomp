// Actor update: commit completed state after every noninitial guard path.
struct VT { char pad[0x190]; short d; short pd; void (*pf)(void *); };
struct S { char pad[0xC]; struct VT *pvt; char pad10[0x48]; int x58; float x5C; char pad60[0xB0]; int x110; int x114; };
extern struct G { char pad[0x3B0C]; void *x3B0C; } g_sw;
extern float D_002DDF0C;
extern int D_002DD318;
extern char D_002E6550[], D_003DA4F0[], g_joy[];
int FScreenObjDone__FP2LO(struct S *p);
void func_00212C50(struct S *p);
int func_001D9880(void *);
int func_00187D80(void *, int);
void ResumeGame__FP9GAMEPAUSEi(struct G *, int);
void RestartJobAtCheckpoint__FP2SW(void *);
// name: SafeHouse port (UpdateFailureScreen)
void UpdateFailureScreen__FP8SCREENRT(struct S *p)
{
    int r = FScreenObjDone__FP2LO(p);
    if (r)
        return;
    func_00212C50(p);
    if (p->x58 == 2 && 0.5f < D_002DDF0C - p->x5C && !func_001D9880(D_002E6550)
        && !func_001D9880(D_003DA4F0) && func_00187D80(g_joy, 0xF0)) {
        ResumeGame__FP9GAMEPAUSEi(&g_sw, 0);
        if (p->x114 == 0 && g_sw.x3B0C) {
            D_002DD318++;
            RestartJobAtCheckpoint__FP2SW(g_sw.x3B0C);
        }
        p->pvt->pf((char *)p + p->pvt->d);
    }
    p->x110 = 1;
    return;
}
