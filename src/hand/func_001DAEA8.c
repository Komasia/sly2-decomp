/* class: items (SafeHouse shop.cpp FItemOwned, the gadget menu's owned flag): is item n acquired - the progress value
 * "powerUps" "mppukfAcquired" "<n>"? (-1: no item.) */
typedef struct CRef { int tagk; int tag; } CRef;
extern char D_002A79A0[], D_002A79A8[], D_002A79B8[];   /* "%d", "powerUps", "mppukfAcquired" */
void sprintf(char *pch, char *pchzFormat, int n);
void func_001D8A38(CRef *pref, char *pchz0, char *pchz1, char *pchz2, int pchzEnd);   /* the progress value at a path */
void __as__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void Decref(CRef *pref) asm("Decref__4CRef");

// name: SafeHouse port (gadget.h FPowerupOwned, orig 0x1DAEA8: the progress powerUps mppukfAcquired <id>)
int FPowerupOwned__Fi(int item)
{
    CRef ref;
    char achItem[0x20];
    CRef refT;
    int fAcquired;
    if (item == -1)
        return 0;
    ref.tagk = -1;
    sprintf(achItem, D_002A79A0, item);
    func_001D8A38(&refT, D_002A79A8, D_002A79B8, achItem, 0);
    __as__4CRefRC4CRef(&ref, &refT);
    Decref(&refT);
    fAcquired = ref.tag;
    Decref(&ref);
    return fAcquired;
}
