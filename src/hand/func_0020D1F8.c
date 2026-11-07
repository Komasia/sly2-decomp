typedef int qword __attribute__((mode(TI)));
struct VE { short d; short pad; void *pf; };
struct LO { char pad[0xC]; struct VE *vt; };
struct X { char pad[0xC]; struct VE *vt; char pad2[0x188 - 0x10]; void *p188; };
struct S { struct LO *po; int k; float t; struct X *x; int n; };
extern struct { float t; float dt; } g_clock;
extern float D_002C3E58;
qword PosOfLo__FP2LO(void *p);
void SetWatchB__FP6WATCHBi(struct S *p, int k);

// name: SafeHouse port (UpdateWatchB)
void UpdateWatchB__FP6WATCHB(struct S *p)
{
    int k;
    if (!p->n)
        return;
    do {
        k = p->k;
        switch (k) {
        case 0: {
            struct X *x = p->x;
            int f;
            struct VE *pe;
            void *pthis;
            if (!x)
                break;
            f = 0;
            pe = &x->vt[73];
            pthis = (char *)x + pe->d;
            if (((int (*)(void *, qword))pe->pf)(pthis, PosOfLo__FP2LO(p->po))) {
                qword v = ((qword (*)(void *))p->po->vt[33].pf)((char *)p->po + p->po->vt[33].d);
                float z;
                __asm__("pextuw %0, $zero, %1" : "=r"(z) : "r"(v));
                if (z < 0.0f)
                    f = 1;
            }
            if (f)
                SetWatchB__FP6WATCHBi(p, 1);
            break;
        }
        case 1:
            if (!p->x)
                SetWatchB__FP6WATCHBi(p, 0);
            else if (g_clock.t - p->t > D_002C3E58 &&
                     !((int (*)(void *, void *))p->po->vt[76].pf)((char *)p->po + p->po->vt[76].d, p->x->p188))
                SetWatchB__FP6WATCHBi(p, 2);
            break;
        case 2:
            if (!p->x || ((int (*)(void *, void *))p->po->vt[76].pf)((char *)p->po + p->po->vt[76].d, p->x->p188))
                SetWatchB__FP6WATCHBi(p, 0);
            break;
        }
    } while (p->k != k);
}
