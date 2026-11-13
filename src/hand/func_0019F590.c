typedef int qword __attribute__((mode(TI)));
struct P;
typedef struct { short d; short pad; void (*pfn)(void *, ...); } VT;
typedef struct E { int x0; int x4; int x8; int xc; qword x10; } E;
struct S58 { char pad[0x70]; qword x70; };
struct SE8 { char pad[0x80]; qword x80; };
struct P {
    char pad0[0xC]; VT *vt; char pad1[0x58-0x10]; struct S58 *x58; char pad2[0xE8-0x5C]; struct SE8 *xe8;
    char pad3[0x1B0-0xEC]; char x1b0[0x240-0x1B0]; qword x240; char pad4[0x2C0-0x250]; char x2c0[0x490-0x2C0];
    qword x490; qword x4a0; char pad5[0x9E0-0x4B0]; char x9e0[4]; int x9e4;
};
struct G { char pad[0x3E60]; int x3e60; };
extern struct G g_sw;
struct D { char pad[0x60]; qword x60; };
extern struct D g_cm;
extern float D_002BF940;
void EntryBestSafe__FP5ACTORPv(void *p, E *e);
struct P *PloPlayerPo__FP2SW(struct G *g);
qword PosSafeEntry__FP5ACTORPvf(struct P *p, E *e, float g);
float TJumpTo__FG9VU_VECTORT0ffff(qword a, qword b, float c, float d, float e, float f);
void func_002046B0(struct P *p, qword q);
void CutCm(struct D *d) asm("CutCm__FP2CM");
void SetJumpKind__FP4JUMPiiP2LO(void *p, int a, int b, int c);
int FIsBasicDerivedFrom__FP5BASIC3CID(int a, int b);
void CheckLoRoot__FP2SWP2LO(struct G *g, int a);
void ChooseJumpTarget__FP4JUMPP2LO(void *p, int a);
void StartFadeLo__FP2LO(int a);
static __inline__ qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
// name: SafeHouse port (RecoverActorTo)
void RecoverActorTo__FP5ACTORPv(struct P *p, E *q)
{
    E e;
    if (!q) {
        EntryBestSafe__FP5ACTORPv(p->x9e0, &e);
        q = &e;
        if (p == PloPlayerPo__FP2SW(&g_sw)) {
            qword r = PosSafeEntry__FP5ACTORPvf(p, &e, 0.0f);
            float g = TJumpTo__FG9VU_VECTORT0ffff(VSub(r, p->x58->x70), p->xe8->x80, 1000.0f, -1000.0f, 1.0f, -1.0f);
            if (D_002BF940 < g) {
                int save = p->x9e4;
                ((void (*)(void *, qword))p->vt[29].pfn)((char *)p + p->vt[29].d, VSub(r, p->x240));
                p->x9e4 = save;
                func_002046B0(p, g_cm.x60);
                ((void (*)(void *, void *))p->vt[30].pfn)((char *)p + p->vt[30].d, p->x1b0);
                CutCm(&g_cm);
                SetJumpKind__FP4JUMPiiP2LO(p->x2c0, 0xB, 0, 0);
                if (e.x4) {
                    if (FIsBasicDerivedFrom__FP5BASIC3CID(e.x0, 0x13) || FIsBasicDerivedFrom__FP5BASIC3CID(e.x0, 0xB) || FIsBasicDerivedFrom__FP5BASIC3CID(e.x0, 0xD) ||
                        FIsBasicDerivedFrom__FP5BASIC3CID(e.x0, 0x27) || FIsBasicDerivedFrom__FP5BASIC3CID(e.x0, 0xC) || FIsBasicDerivedFrom__FP5BASIC3CID(e.x0, 0x22) ||
                        FIsBasicDerivedFrom__FP5BASIC3CID(e.x0, 0x26)) {
                        CheckLoRoot__FP2SWP2LO(&g_sw, e.x0);
                        ChooseJumpTarget__FP4JUMPP2LO(p->x2c0, e.x0);
                    }
                }
                StartFadeLo__FP2LO(g_sw.x3e60);
                return;
            }
        }
    }
    p->x490 = *(qword *)q;
    p->x4a0 = q->x10;
    SetJumpKind__FP4JUMPiiP2LO(p->x2c0, 0xA, 0, 0);
}
