struct VE { short d; short pad; int (*pf)(void *, int); };
struct O { char pad[0xC]; struct VE *vt; };
struct S { struct O *po; int k; float t; int n; };
extern struct { float t; float dt; } g_clock;
extern float D_002C3DF0;
int FWatchA__FP6WATCHA(struct S *p);
void SetWatchA__FP6WATCHAi(struct S *p, int k);

// name: SafeHouse port (UpdateWatchA)
void UpdateWatchA__FP6WATCHA(struct S *p)
{
    int f, k;
    if (!p->n)
        return;
    f = FWatchA__FP6WATCHA(p);
    do {
        k = p->k;
        switch (k) {
        case 0:
            if (f)
                SetWatchA__FP6WATCHAi(p, 1);
            break;
        case 1:
            if (!f)
                SetWatchA__FP6WATCHAi(p, 0);
            else if (g_clock.t - p->t > D_002C3DF0 && !p->po->vt[76].pf((char *)p->po + p->po->vt[76].d, 0x4000))
                SetWatchA__FP6WATCHAi(p, 2);
            break;
        case 2:
            if (!f)
                SetWatchA__FP6WATCHAi(p, 0);
            break;
        }
    } while (p->k != k);
}
