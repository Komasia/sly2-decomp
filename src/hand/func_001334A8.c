/* All of the object's listener entries freed (ReleaseAsega). */
struct LISTENER { int id; int c; struct LISTENER *pnext; };   /* field: SafeHouse port (update.cpp) */
struct LO { int pad[2]; struct LISTENER *plistenerFirst; };   /* LO +0x8 */
extern char D_003E1144[];
void func_0011CD98(void *, void *);
void func_001334A8(struct LO *plo) {
    struct LISTENER *plistener = plo->plistenerFirst;
    while (plistener) { struct LISTENER *plistenerNext = plistener->pnext; func_0011CD98(D_003E1144, plistener); plistener = plistenerNext; }
    plo->plistenerFirst = 0;
}
