/* RemoveLoListener: one count fewer of the listener id; the entry is freed when none is left. SafeHouse port. */
struct LISTENER { int id; int c; struct LISTENER *pnext; };   /* field: SafeHouse port (update.cpp) */
struct LO { int pad[2]; struct LISTENER *plistenerFirst; };   /* LO +0x8 */
extern char D_003E1144[];
void func_0011CD98(void *, void *);
// name: SafeHouse port (update.h: 0x133448 RemoveLoListener)
void RemoveLoListener__FP2LOi(struct LO *plo, int id) {
    struct LISTENER **pplistener;
    struct LISTENER *plistener;
    for (pplistener = &plo->plistenerFirst; (plistener = *pplistener) != 0; pplistener = &plistener->pnext) { if (plistener->id == id) { if (--plistener->c <= 0) { *pplistener = plistener->pnext; func_0011CD98(D_003E1144, plistener); } break; } }
}
