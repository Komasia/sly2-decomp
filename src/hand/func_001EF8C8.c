typedef int qword __attribute__((mode(TI)));
union V { qword q; float f[4]; };
struct VTE { short d; short pad; void (*pf)(void *, qword); };
struct S { char pad[0xC]; struct VTE *vt; char pad2[0x150-0x10]; int n150; };
struct G { char pad[0x30]; qword q; };
extern struct G D_002DDFA0;
void UpdateSo__FP2SOf(struct S *p);
qword PosOfLo__FP2LO(struct S *p);
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
// name: SafeHouse port (UpdateSky)
void UpdateSky__FP3SKY(struct S *p)
{
    union V v;
    UpdateSo__FP2SOf(p);
    v.q = D_002DDFA0.q;
    if (!p->n150) v.f[2] = GetZ(PosOfLo__FP2LO(p));
    p->vt[29].pf((char *)p + p->vt[29].d, v.q);
}
