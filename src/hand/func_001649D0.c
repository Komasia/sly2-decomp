struct X { char pad[0x64]; void *f64; void *f68; };
struct G { char pad[0x3B0C]; struct X *f3b0c; };
extern struct G g_sw;
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct G *pg, int kind, int n, int m, int c, void **apv);
int FTaskDone__FP4TASK(void *p);
void func_00162908(struct X *p);
void JobSwitch__FP3JOB(struct X *p);
// name: SafeHouse port (ChooseJob)
void ChooseJob__Fv(void)
{
    struct X *apx[256];
    struct X *pxFound = 0;
    int c = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 5, 0x84, 0, 0x100, (void **)apx);
    int i;
    for (i = 0; i < c; i++) {
        struct X *px = apx[i];
        if (FTaskDone__FP4TASK(px->f64) && !FTaskDone__FP4TASK(px->f68))
            pxFound = px;
    }
    if (pxFound != g_sw.f3b0c) {
        if (g_sw.f3b0c)
            func_00162908(g_sw.f3b0c);
        if (pxFound)
            JobSwitch__FP3JOB(pxFound);
    }
}
