typedef int qword __attribute__((mode(TI)));
struct V3 { float x, y, z; float w; };
struct O { char pad[0x54]; float f54; float f58; float f5C; };
struct P { char pad[0x10]; int n10; char pad2[0x6C - 0x14]; int n6C; float f70; char x74[0xC]; struct V3 v80; struct V3 v90; };
struct SW { char pad[0x4034]; struct O *p4034; };
extern struct SW g_sw;
void func_001FCF70(void);
void func_002330D0(int, int, int, int, int, int, int, void (*)(void), long);
void *PloPlayerPo__FP2SW(struct SW *);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
qword PosOfLo__FP2LO(void *);
void SetHeldNoise__FPP5NOISEG9VU_VECTORiP2LO(struct O *, qword, void *, void *);
static inline float Eval(struct V3 *pv, float t)
{
    return pv->x + t * (pv->y + t * pv->z);
}
void func_001FDA48(struct P *p)
{
    struct O *po;
    qword q;
    void *pv;
    if (!p->n10) {
        p->f70 = 0.0f;
    } else if (!p->n6C) {
        p->n6C = 1;
        func_002330D0(0x524B5553, 0xB, 0, 0, 0, 0, 0, func_001FCF70, (long)p);
    }
    po = 0;
    pv = PloPlayerPo__FP2SW(&g_sw);
    if (pv && FIsBasicDerivedFrom__FP5BASIC3CID(pv, 0x34) && 0.5f < p->f70) {
        float y;
        po = g_sw.p4034;
        q = PosOfLo__FP2LO(pv);
        po->f54 = Eval(&p->v80, p->f70);
        y = Eval(&p->v90, p->f70);
        po->f5C = y;
        po->f58 = -y;
    }
    SetHeldNoise__FPP5NOISEG9VU_VECTORiP2LO(po, q, pv, p->x74);
}
