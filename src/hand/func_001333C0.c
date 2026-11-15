/* AddLoListener: one more count of the listener id on the object (LO +0x8), a new entry {id, 1} at the head when it is
 * not there yet (from the slot heap D_003E1144). Layout: SafeHouse port (update.cpp LISTENER). */
struct LISTENER { int id; int c; struct LISTENER *pnext; };   /* field: SafeHouse port (update.cpp) */
struct LO { int pad[2]; struct LISTENER *plistenerFirst; };   /* LO +0x8 */
extern char D_003E1144[];
struct LISTENER *func_0011CCC0(void *);
// name: SafeHouse port (update.h: 0x1333C0 AddLoListener, counted by id)
void AddLoListener__FP2LOi(struct LO *plo, int id) {
    struct LISTENER *plistener;
    for (plistener = plo->plistenerFirst; plistener; plistener = plistener->pnext) {
        if (plistener->id == id) { plistener->c++; return; }
    }
    {
        register struct LISTENER *plistenerNew __asm__("$3") = func_0011CCC0(D_003E1144);
        __asm__("" : "+r"(plistenerNew));
        plistenerNew->id = id;
        { register int one __asm__("$2") = 1; __asm__("" : "+r"(one)); plistenerNew->c = one; }
        plistenerNew->pnext = plo->plistenerFirst;
        plo->plistenerFirst = plistenerNew;
    }
}
