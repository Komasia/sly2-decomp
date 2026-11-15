/* PostLoadActorBooty: the booty the save says the actor carries (its progress node's key D_002A4DB0; none for -1 / 0):
 * returned to its stand when D_003E1084 has 0x40, else given to it. */
#include "vtbl.h"
struct ACTOR { char pad[0xC]; VTENT *vt; };
struct CRef { int tagk; int tag; };
extern char D_002A4DB0[];
extern int D_003E1084;
void func_001D8A38(struct CRef *ref, void *a, void *b, int c);
void Decref(struct CRef *ref) asm("Decref__4CRef");
void AkeyReturnBooty__FP5ACTORi(struct ACTOR *pactor, int idBooty);
void GiveActorBooty__FP5ACTORi(struct ACTOR *pactor, int idBooty);
// name: SafeHouse port (PostLoadActorBooty)
void PostLoadActorBooty__FP5ACTOR(struct ACTOR *pactor)
{
    struct CRef ref;
    int idBooty;
    VTENT *e = &pactor->vt[103];
    func_001D8A38(&ref, ((void *(*)(void *))e->pfn)(VT_THIS(pactor, e)), D_002A4DB0, 0);
    idBooty = ref.tag;
    Decref(&ref);
    if ((unsigned int)(idBooty + 1) < 2) return;
    if (D_003E1084 & 0x40) AkeyReturnBooty__FP5ACTORi(pactor, idBooty);
    else GiveActorBooty__FP5ACTORi(pactor, idBooty);
}
