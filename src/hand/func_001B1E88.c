#include "vec.h"
struct P { char pad[0x5C]; int n5C; char pad1[0x210 - 0x60]; int n210; int pad2[3]; struct VECTOR v220; int n230; int a234[12]; int n264; int n268; float g26C; };
void func_001305B8(int n, struct P *p, int c, int *pn, float g0, float g1);
int func_0012DCA0(struct P *p, int n, int a, int b, float g0, float g1);
void func_001B1E88(struct P *p, int n, struct VECTOR *pv)
{
    struct VECTOR v;
    v = *pv;
    p->n210 = n;
    p->v220 = v;
    func_001305B8(p->n230, p, 8, p->a234, 0.0f, 1.0f);
    if (p->n264)
        p->n268 = func_0012DCA0(p, p->n5C, 0, 5, p->g26C, 0.0f);
}
