typedef int qword __attribute__((mode(TI)));
struct G;
extern struct G g_sw;
extern char D_002F66B0[];
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct S { char pad[0xEC]; void *xEC; char pad1[0x138 - 0xF0]; int x138; int k; float t140; int x144; int c; int *a; int x150; int x154; float t158; float dt; };
void func_001A5E28(struct S *p);
void QueueMovie__FPUcPv(void *a, int b);
void func_0022B490(struct G *p, int a, int b, int c, int d, int e);
void *func_001C4840(struct G *pg);
qword func_001A62E8(void *p);
qword ConvertPos__FP2LOT0G9VU_VECTOR(int a, struct S *p, qword q);
int func_00118FB0(void *p, int n, qword q);
void SetExitState__FP2LOi(struct S *p, int k);
void TriggerExit__FP4EXIT(struct S *p);
// name: SafeHouse port (UpdateExit)
void UpdateExit__FP2LO(struct S *p)
{
    func_001A5E28(p);
    switch (p->k) {
    case 4:
        if (0.0f < p->t158 && p->t158 <= g_clock.t) {
            int i;
            for (i = 0; i < p->c; i++)
                QueueMovie__FPUcPv(D_002F66B0, p->a[i]);
            func_0022B490(&g_sw, p->x144, p->x150, -1, p->x138 ? 0x20 : 0, p->x154);
            p->t158 = 0.0f;
        }
        break;
    case 0: case 1: case 3: {
        void *pj = func_001C4840(&g_sw);
        union { qword q; } u;
        int f;
        if (!pj) return;
        u.q = ConvertPos__FP2LOT0G9VU_VECTOR(0, p, func_001A62E8(pj));
        f = func_00118FB0(p->xEC, 0x7FFFFFFF, u.q) != 0;
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
