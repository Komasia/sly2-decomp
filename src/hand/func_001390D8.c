/* PblipgNew (Sly 1 blip.c, by module order): a new blip group (0x460 bytes, vtable D_002CB5D8) from the world's slot
 * heap +0x4070 (none when +0x407C is clear and +0x4084 set), appended to the world's list 0x1C and initialised (vt slots
 * 7, 11, 15). */
#include "vtbl.h"
struct BLIPG { int pframe; int psidebag; int f8; VTENT *vt; char pad[0x460 - 0x10]; };
struct SW { char pad[0x4070]; int slotheapBlipg; char pad2[0x407c - 0x4074]; int f407c; int f4080; int f4084; };
extern VTENT D_002CB5D8[];   /* the BLIPG vtable */
struct BLIPG *func_0011CCC0(void *);
void s1_memset(void *, int, int) asm("memset");
void *func_0015E3A8(struct SW *, int);
void func_0011A070(void *, struct BLIPG *);
struct BLIPG *func_001390D8(struct SW *psw) {
    struct BLIPG *pblipg;
    int i;
    if (!psw->f407c && psw->f4084) return 0;
    pblipg = func_0011CCC0(&psw->slotheapBlipg);
    s1_memset(pblipg, 0, 0x460);
    pblipg->pframe = 0;
    pblipg->psidebag = 0;
    pblipg->vt = D_002CB5D8;
    i = 31;
    while (--i != -1) ;   /* empty array-element ctor loop (31 elements) from inlined C++ ctor */
    func_0011A070(func_0015E3A8(psw, 0x1c), pblipg);
    ((void (*)(void *))pblipg->vt[7].pfn)(VT_THIS(pblipg, &pblipg->vt[7]));
    ((void (*)(void *))pblipg->vt[11].pfn)(VT_THIS(pblipg, &pblipg->vt[11]));
    ((void (*)(void *))pblipg->vt[15].pfn)(VT_THIS(pblipg, &pblipg->vt[15]));
    return pblipg;
}
