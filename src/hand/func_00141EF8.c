#include "vtbl.h"
struct E { int id; int a, b; };
struct P { char pad[0xC]; VTENT *vt; char pad2[0x1180 - 0x10]; struct E ae[3]; };
struct CRef { int tagk; int tag; };
extern char D_002A4D50[];
extern char D_002A4D58[];
int sprintf(char *, const char *, ...);
void func_001D8A38(struct CRef *r, void *a, void *b, char *c, int d);
void Decref(struct CRef *r) asm("Decref__4CRef");
void func_00141EF8(struct P *p)
{
    int i;
    for (i = 0; i < 3; i++) {
        char ach[16];
        struct CRef r;
        VTENT *e;
        sprintf(ach, D_002A4D50, i);
        e = &p->vt[103];
        func_001D8A38(&r, ((void *(*)(void *))e->pfn)(VT_THIS(p, e)), D_002A4D58, ach, 0);
        p->ae[i].id = r.tag;
        Decref(&r);
    }
    {
        VTENT *e = &p->vt[105];
        ((void (*)(void *))e->pfn)(VT_THIS(p, e));
    }
}
