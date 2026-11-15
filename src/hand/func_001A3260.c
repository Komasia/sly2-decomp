/* func_001A3260 (0x1A3260): the world's default light: if no light (the list D_003E04F8, linked by LO +0x20) has
 * fNoBake (+0x160) clear, makes one (PloNew: cid 4 LIGHT, oid 0x188): directional, turned toward (-0.2, 0.3, -1)
 * (vtable slot 30 with the look-at matrix), strength 255, angle 240. SafeHouse lightsw.cpp. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2
	mfc1 %1,%3
	pextlw %0,%1,%0
	mfc1 %1,%4
	pcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
struct LO;
struct LO { int x0, x4, x8; VTENT *vt; char pad[0x20 - 0x10]; struct LO *x20; char pad2[0x160 - 0x24]; int x160; };
extern struct LO *g_plightFirst __asm__("D_003E04F8");  /* the world's lights */
#define CID_LIGHT 4
#define OID_DEFAULT_LIGHT 0x188
#define VT_SET_ROTATION 30
extern qword g_normalZ;
struct LO *PloNew__F3CIDP2SW3OIDi(int cid, int psw, int oid, int n);
void BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1(M3 *pm, qword v, qword w);
void func_001A3610(struct LO *plight, float strength);  /* sets the strength */
void func_001A3630(struct LO *plight, float angle);     /* sets the angle */
void func_001A3260(void)
{
    struct LO *p;
    M3 c;
    union { qword q; float f; } dir;
    M3 m;
    for (p = g_plightFirst; p; p = p->x20) {
        if (p->x160 == 0) break;
    }
    if (p) return;
    p = PloNew__F3CIDP2SW3OIDi(CID_LIGHT, 0, OID_DEFAULT_LIGHT, -1);
    dir.q = Make(-0.2f, 0.3f, -1.0f);
    BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1(&m, dir.q, g_normalZ);
    c = m;
    ((void (*)(struct LO *, M3 *))p->vt[VT_SET_ROTATION].pfn)((struct LO *)VT_THIS(p, &p->vt[VT_SET_ROTATION]), &c);
    func_001A3610(p, 255.0f);
    func_001A3630(p, 240.0f);
}
