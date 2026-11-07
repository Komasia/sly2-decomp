typedef struct CRef { int m_tagk; union { int n; float g; } u; } CRef;
struct G { char pad[0x3B58]; void *apA[9]; void *apB[9]; };
extern struct G g_sw;
extern char D_003D4A60[];
extern int D_002BE26C;
extern int D_002BE2D0[];
struct S { char pad[0x118]; int i; };
void NProgress(CRef *pref, void *p, void *q);
void func_00129EC8(CRef *pref);
// name: SafeHouse port (CmovieOpen)
int CmovieOpen__FP6EPMENU(struct S *p)
{
    void *pA, *pB;
    int n;
    CRef ref;
    float g;
    if (D_002BE26C)
        return 0x10;
    n = D_002BE2D0[p->i];
    pA = g_sw.apA[p->i];
    pB = g_sw.apB[p->i];
    NProgress(&ref, pA, D_003D4A60);
    g = ref.u.g;
    func_00129EC8(&ref);
    if (g == 0.0f) {
        n -= 2;
    } else {
        int c;
        NProgress(&ref, pB, D_003D4A60);
        c = ref.u.n;
        func_00129EC8(&ref);
        if (c <= 99)
            n--;
    }
    return n;
}
