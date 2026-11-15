/* The deferred call with the given id cancelled (SafeHouse gamebif.cpp bif 106): off the world's list (SW +0x39F0),
 * its form released (the CPair freed to the slot heap D_004520A8 when no reference is left) and the entry freed. */
struct CPair { int cref; int f4; int refCar[2]; int spCdr; };
struct DEFEV { int t; int plo; struct CPair *ppair; int id; struct DEFEV *pnext; };
struct SW { char pad[0x39f0]; struct DEFEV *pdefevFirst; int f39f4; int f39f8; int slotheapDefev; };
extern char D_004520A8[];   /* the CPairs' slot heap */
void func_0011A118(void *pdl, struct DEFEV *pdefev);   /* RemoveDlEntry */
void func_00256D40(void *psp, int n);
void Decref(void *pref) asm("Decref__4CRef");
void func_002550F8(struct CPair *ppair);
void func_0011CD98(void *pslotheap, void *pv);
void func_00133130(struct SW *psw, int id)
{
    struct DEFEV *pdefev;
    if (id == -1) return;
    for (pdefev = psw->pdefevFirst; pdefev; pdefev = pdefev->pnext) {
        if (pdefev->id == id) {
            struct CPair *ppair;
            func_0011A118(&psw->pdefevFirst, pdefev);
            ppair = pdefev->ppair;
            if (--ppair->cref == 0 && ppair) {
                func_00256D40(&ppair->spCdr, 2);
                Decref(ppair->refCar);
                func_002550F8(ppair);
                func_0011CD98(D_004520A8, ppair);
            }
            func_0011CD98(&psw->slotheapDefev, pdefev);
            return;
        }
    }
}
