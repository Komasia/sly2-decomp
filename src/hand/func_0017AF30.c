typedef int qword __attribute__((mode(TI)));
struct G { char pad[0x4028]; void *p4028; };
extern struct G g_sw;
extern void *D_002BE6D0[];
extern int D_002BE6E8[];
struct VTE { short d; short pad; void *pfn; };
struct O { char pad[0xC]; struct VTE *vt; };
struct C { int pad; void *p4; void *p8; int nC; };
struct A { char pad[0x33C]; int n33C; };
struct S { char pad[0x10]; struct A *p10; char pad2[0x2C]; struct C *p40; char pad3[0xC]; int n50; int pad4; int n58; };
struct M { int n0; int pad; int n8; int nC; int n10; char pad2[0x30]; int n44; };
struct X { int a; int pad[7]; qword v; qword pad2; };
int Message__7JOBMOVEiPv(struct S *p, int msg, struct M *pm);
int PasegaOfKinde__FP5KINDE(struct C *c);
int FKindeDone__FP5KINDE(struct C *c);
void StopKinde__FP5KINDE(struct C *c);
void PlayKinde__FP5KINDEP5GUARDif(struct C *c, struct A *a, int fl, float g);
float *PeventLaunch__FP5KINDEi(void *p, void *q);
void SetAsegaTime__FP5ASEGAiff(void *p, float a, float b, int n);
void SetState__5JOBB1i(struct S *p, int n);
struct O *PloFindSwNearest__FP2LO3OIDii(struct G *g, int a, int b, int c);
void *s1_memset(void *p, int c, int n) asm("memset");
qword PosOfLo__FP2LO(struct A *a);
void func_00156698(void *p, qword v, struct A *a);
// name: SafeHouse port (JOBB1::Message)
int Message__5JOBB1iPv(struct S *p, int msg, struct M *pm) {
    if (Message__7JOBMOVEiPv(p, msg, pm)) return 1;
    switch (msg) {
    case 9:
        if (p->p40 == 0) return 0;
        if (PasegaOfKinde__FP5KINDE(p->p40) != pm->n0) return 0;
        if (pm->n8 == 0x3D) p->n58 = 0;
        return 0;
    case 0xC:
        {
            int i, n;
            float g;
            struct G *pg;
            struct O *o;
            struct A *a;
            if (pm->nC != 0x200000) return 0;
            if (!(pm->n44 & 8)) return 0;
            if (!p->n50) return 0;
            if (FKindeDone__FP5KINDE(p->p40)) {
                StopKinde__FP5KINDE(p->p40);
                PlayKinde__FP5KINDEP5GUARDif(p->p40, p->p10, p->p40->nC | 1, 0.0f);
            }
            p->n58++;
            g = 0.0f;
            i = 4; if (p->n58 <= 3) i = p->n58;
            while (i > 0) {
                float *r = PeventLaunch__FP5KINDEi(p->p40->p4, D_002BE6D0[i]);
                if (r) { g = *r; break; }
                i--;
            }
            SetAsegaTime__FP5ASEGAiff(p->p40->p8, g, 1.0f, 0);
            SetState__5JOBB1i(p, 0);
            o = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, D_002BE6E8[i], 0);
            if (o) {
                struct X x;
                struct VTE *e;
                s1_memset(&x, 0, sizeof x);
                x.a = 5;
                x.v = PosOfLo__FP2LO(p->p10);
                e = &o->vt[0x33];
                ((void (*)(void *, struct X *))e->pfn)((char *)o + e->d, &x);
            }
            a = p->p10;
            {
                int m = a->n33C + pm->n10;
                a->n33C = m < 5 ? 5 : m;
            }
            func_00156698(g_sw.p4028, PosOfLo__FP2LO(p->p10), p->p10);
            return 1;
        }
    }
    return 0;
}
