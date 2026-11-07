typedef int qword __attribute__((mode(TI)));
extern char g_sw[];
struct S { char pad[0x20]; qword v; char pad2[0xB8 - 0x30]; int f; };
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *p, int a, int b, int c, int d, int *e);
int FPointInShape__FP2LOG9VU_VECTOR(int a, qword v);
void func_00201F90(struct S *p)
{
    int a[16];
    int n, i;
    int *pa;
    p->f = 0;
    n = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(g_sw, 0x505, 0x19, 0, 16, a);
    for (i = 0; i < n; i++) {
        if (FPointInShape__FP2LOG9VU_VECTOR(a[i], p->v)) {
            p->f = 1;
            break;
        }
    }
}
