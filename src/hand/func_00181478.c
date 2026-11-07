typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x1C0]; int n1C0; int x1C4; void *p1C8; void *p1CC; };
extern void UpdateSo__FP2SOf(struct O *p);
extern qword PosOfLo__FP2LO(void *p);
extern int FShipSegmentDone__FP2LO(struct O *p);
extern void SetDockState__FP2LOi(struct O *p, int n);
extern void *D_002DFB80;
extern float D_002BE880;
static __inline__ float GDist(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %1, %1" : "=j"(d) : "j"(d));
    __asm__("vaddw.x %0, $vf0, $vf0w\n\tvadday.x ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=&j"(one), "+j"(d));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static __inline__ int FClose(float g)
{
    int f = 1;
    if (g < D_002BE880) {} else f = 0;
    return f;
}
// name: SafeHouse port (UpdateDock)
void UpdateDock__FP2LO(struct O *p)
{
    int s;
    UpdateSo__FP2SOf(p);
    do {
        s = p->n1C0;
        switch (s) {
        case 0:
            if (D_002DFB80) {
                if (FClose(GDist(PosOfLo__FP2LO(D_002DFB80), PosOfLo__FP2LO(p->p1CC)))) {
                    p->p1C8 = D_002DFB80;
                    SetDockState__FP2LOi(p, 1);
                }
            }
            break;
        case 1:
            if (FShipSegmentDone__FP2LO(p))
                SetDockState__FP2LOi(p, 2);
            break;
        }
    } while (p->n1C0 != s);
}
