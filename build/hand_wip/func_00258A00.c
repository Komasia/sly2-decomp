// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
typedef struct { char pad[0x10]; int x10; char pad2[0x1C]; int x30; } T;
typedef struct { char pad[0xE4]; T *xE4; } S;
typedef struct { int a, b; } P;
T *func_00258658(S *, int); int func_001AE2A0(P *);
void func_00258A00(S *p, int k)
{
    T *t;
    P q;
    int v, sz;
    if (p->xE4->x10 == k) return;
    if (p->xE4->x10 != 0) return;
    t = func_00258658(p, 1);
    t->x10 = k;
    switch (k) {
    case 1: q.a = 0x20; break;
    case 2: v = -1; goto store;
    case 3: q.a = 0x30; break;
    default: return;
    }
    q.b = 0x10;
    v = func_001AE2A0(&q);
store:
    t->x30 = v;
}