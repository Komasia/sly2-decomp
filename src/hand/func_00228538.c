typedef int qword __attribute__((mode(TI)));
struct G;
extern struct G g_sw;
extern char D_002F66B0[];
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct S { char pad[0xEC]; void *xEC; char pad1[0x138 - 0xF0]; int x138; int k; float t140; int x144; int c; int *a; int x150; int x154; float t158; float dt; };
void UpdateLo__FP2LO(struct S *p);
void QueueMovie__FPUcPv(void *a, int b);
void RequestTransition__FP2SWPUc3OIDT2iT2(struct G *p, int a, int b, int c, int d, int e);
void *PloPlayerPo__FP2SW(struct G *pg);
qword PosOfLo__FP2LO(void *p);
qword ConvertPos__FP2LOT0G9VU_VECTOR(int a, struct S *p, qword q);
int IbspFindPoint__FP6BSPREFP6VECTORG9VU_VECTOR(void *p, int n, qword q);
void SetExitState__FP2LOi(struct S *p, int k);
void TriggerExit__FP4EXIT(struct S *p);
// name: SafeHouse port (UpdateExit)
void UpdateExit__FP2LO(struct S *p)
{
    UpdateLo__FP2LO(p);
    switch (p->k) {
    case 4:
        if (0.0f < p->t158 && p->t158 <= g_clock.t) {
            int i;
            for (i = 0; i < p->c; i++)
                QueueMovie__FPUcPv(D_002F66B0, p->a[i]);
            RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, p->x144, p->x150, -1, p->x138 ? 0x20 : 0, p->x154);
            p->t158 = 0.0f;
        }
        break;
    case 0: case 1: case 3: {
        void *pj = PloPlayerPo__FP2SW(&g_sw);
        union { qword q; } u;
        int f;
        if (!pj) return;
        u.q = ConvertPos__FP2LOT0G9VU_VECTOR(0, p, PosOfLo__FP2LO(pj));
        f = IbspFindPoint__FP6BSPREFP6VECTORG9VU_VECTOR(p->xEC, 0x7FFFFFFF, u.q) != 0;
        switch (p->k) {
        case 3:
            if (f) TriggerExit__FP4EXIT(p);
            break;
        case 1:
            if (f) SetExitState__FP2LOi(p, 0);
            else if (g_clock.t - p->t140 > p->dt) SetExitState__FP2LOi(p, 3);
            break;
        case 0:
            if (!f) SetExitState__FP2LOi(p, 1);
            break;
        }
        break;
    }
    case 2:
        break;
    }
}
