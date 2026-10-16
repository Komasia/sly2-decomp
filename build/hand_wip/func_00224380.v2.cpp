// Complete actor contact-transition WIP; actual scalar member is initialized and consumed.
typedef int qword __attribute__((mode(TI)));
struct O { int x0; struct S *p; };
struct SIDE { struct O *po; int x4; int x8; struct S *pOther; char pad[0x30]; };
struct EDGE { struct SIDE as[2]; qword v80; char pad[0xC]; int k9C; char pad2[0xC]; struct EDGE *pNext; };
struct LN { struct EDGE *pe; struct LN *pNext; };
struct Q { char pad[0x60]; int id; struct LN *pln; };
struct S { char pad[0xEC]; struct Q *pq; char pad1[0x150 - 0xF0]; int x150; float t154; int x158; char pad2[0x190 - 0x15C]; qword v190; struct S *x1A0; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern float D_002C42E0;
extern float D_002C3C60[];
extern "C" void func_001F4F10(struct S *p);
extern "C" int func_00224638(struct S *p);
extern "C" int func_00224508(struct S *p, struct S *q);
struct SCALAR {qword q;};
static inline void InitScalar(SCALAR &home,const float &f){int bits=*(const int*)&f;__asm__("qmtc2.ni %1,%0":"=j"(home.q):"r"(bits));}
static inline qword Scale(const qword &direction,const SCALAR &scalar){qword result;__asm__("vmulx.xyzw %0,%1,%0x":"=j"(result):"j"(direction),"0"(scalar.q));return result;}
extern "C" void func_00224380(struct S *p)
{
    struct S *q;
    struct EDGE *pe;
    struct LN *pln;
    int id;
    func_001F4F10(p);
    if (!p->x150 && D_002DDED0.t - p->t154 < D_002C42E0) return;
    pln = p->pq->pln;
    id = p->pq->id;
    for (; pln; pln = pln->pNext) {
        pe = pln->pe;
        while (pe) {
            int i = pe->as[0].x8 != id;
            if (pe->as[i].po->p != p) {
                pe = pe->pNext;
                continue;
            }
            q = pe->as[1 - i].pOther;
            if (pe->k9C != 8 && func_00224638(p) && func_00224508(p, q)) {
                SCALAR home;
                p->x1A0=q;
                p->x158=2;
                InitScalar(home,D_002C3C60[i]);
                p->v190=Scale(pe->v80,home);
            } else if (!p->x150 && p->x158 == -1) {
                p->x158 = 4;
            }
            pe = pe->pNext;
        }
    }
}
