/* The actor's three ability slots loaded from the save (the player's progress node (vt slot 103) key D_002A4D58 with the
 * slot's name from D_002A4D50 and its index); then the ability display (vt slot 105). */
#include "vtbl.h"
struct ABSLOT { int id; int a, b; };   /* a button's ability slot (SafeHouse gadget.h) */
struct ACTOR { char pad[0xC]; VTENT *vt; char pad2[0x1180 - 0x10]; struct ABSLOT aabslot[3]; };
struct CRef { int tagk; int tag; };
extern char D_002A4D50[];
extern char D_002A4D58[];
int sprintf(char *, const char *, ...);
void func_001D8A38(struct CRef *ref, void *a, void *b, char *c, int d);
void Decref(struct CRef *ref) asm("Decref__4CRef");
void func_00141EF8(struct ACTOR *pactor)
{
    int i;
    for (i = 0; i < 3; i++) {
        char achKey[16];
        struct CRef ref;
        VTENT *e;
        sprintf(achKey, D_002A4D50, i);
        e = &pactor->vt[103];
        func_001D8A38(&ref, ((void *(*)(void *))e->pfn)(VT_THIS(pactor, e)), D_002A4D58, achKey, 0);
        pactor->aabslot[i].id = ref.tag;
        Decref(&ref);
    }
    {
        VTENT *e = &pactor->vt[105];
        ((void (*)(void *))e->pfn)(VT_THIS(pactor, e));
    }
}
