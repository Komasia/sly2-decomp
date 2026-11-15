/* MaskOfList (0x207B10): the guard state mask of an option's list of state indices (at most 16). */
struct CRef { int tagk; int tag; };
void func_002013D8(struct CRef *pref, void *plist, int grf, int cnMax, int *pcn, int *an);   /* the list's ints */
unsigned long func_00207A40(int cst, int *ast);
void Decref(struct CRef *pref) asm("Decref__4CRef");
// name: SafeHouse port (MaskOfList)
unsigned long MaskOfList__FPv(void *plist) { int ast[16]; struct CRef ref; int cst; unsigned long grf; func_002013D8(&ref, plist, 0x1010, 0x10, &cst, ast); grf = func_00207A40(cst, ast); Decref(&ref); return grf; }
