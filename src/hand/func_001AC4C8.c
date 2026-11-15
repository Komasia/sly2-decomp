/* func_001AC4C8 (0x1AC4C8): reads a save slot from the card: the slot cleared, its file's directory entry read
 * (0x1ABFC0) into the slot's entry; a file with the wrong attributes is error 0x14, one of the wrong size (not
 * 0x5408) 0x1C; else its data read. */
#include "h5_mc.h"
#define CB_SAVE 0x5408
#define GRFATTR_CHECK 0xD4
#define GRFATTR_FILE 0x4
void s1_memset(void *p, int c, int n) asm("memset");
void func_001ABB10(void *pmc, void *pslot, char *szName);
int func_001ABFC0(void *pmc, char *szName, void *pdirent);
int func_001AC9A0(void *pmc, char *szName, void *pv, int cb);
int func_001AC4C8(void *pmc, struct MCSLOT *pslot)
{
    char szName[0x50];
    int nErr;
    s1_memset(pslot, 0, sizeof(struct MCSLOT));
    func_001ABB10(pmc, pslot, szName);
    nErr = func_001ABFC0(pmc, szName, &pslot->dirent);
    if (nErr)
        return nErr;
    if ((*(int *)&pslot->dirent.grfattr & GRFATTR_CHECK) != GRFATTR_FILE)
        return 0x14;
    if (pslot->dirent.cb != CB_SAVE)
        return 0x1C;
    return func_001AC9A0(pmc, szName, pslot, CB_SAVE);
}
