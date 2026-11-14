struct X { int a; int b; int c; };
struct E { int a[4]; };
struct S { char pad[0x180]; int x180; int x184; char p1[0x38]; int n; float t; char p2[0x48]; struct X x; int p3; struct E ae[1]; };
#include "clock.h"
static __inline__ void ClearX(struct X *px) { px->a = px->b = px->c = 0; }
void PlayHackSeg__FP2LOP6HACKSO(struct S *p, struct E *pe);
// name: SafeHouse port (SetEnemyState)
void SetEnemyState__FP2LOi(struct S *p, int n)
{
    if (p->n == n) return;
    if (p->n == -1) p->x184 = p->x180;
    p->n = n;
    p->t = g_clock.t;
    switch (n) {
    case 0: case 1: case 2: case 4:
        ClearX(&p->x);
        break;
    case 3:
        break;
    }
    PlayHackSeg__FP2LOP6HACKSO(p, n == -1 ? 0 : &p->ae[n]);
}
