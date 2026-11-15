/* class: progress path (SafeHouse savedata.h: "orig 0x1D87C0 + 0x1D7ED8"): build a KEY from a NULL-terminated list of
 * path element strings (pchz, then the va_list): each is its name's symbol, else its number (atoi). The symbols
 * go on the stack heap. */
#include "h3_progress.h"
typedef char *va_list;
#define va_arg_pch(ap) (*(char **)((ap += 8) - 8))
struct MSG { int cb; int nKind; };
extern LAYOUT D_003E0EA8;             /* the progress layout */
void *PvAllocStackImpl__Fi(struct MSG *pmsg);
int SymFromName__FP6LAYOUTPc(NAMETABLE *pnametable, char *pchz);
static inline int NFind(LAYOUT *playout, char *pchz) { return SymFromName__FP6LAYOUTPc(&playout->nametable, pchz); }
short atoi(char *pchz);

void func_001D87C0(char *pchz, va_list ap, KEY *pkey)
{
    va_list apSave = ap;
    char *pchzT;
    int isym;
    pkey->csym = 0;
    pkey->asym = 0;
    for (pchzT = pchz; pchzT; pchzT = va_arg_pch(ap))
        pkey->csym++;
    if (pkey->csym) {
        struct MSG msg;
        msg.cb = pkey->csym * 2;
        msg.nKind = 0x10;
        pkey->asym = PvAllocStackImpl__Fi(&msg);
        ap = apSave;
        for (pchzT = pchz, isym = 0; pchzT; pchzT = va_arg_pch(ap), isym++) {
            int sym = NFind(&D_003E0EA8, pchzT);
            if (sym == -1)
                pkey->asym[isym] = atoi(pchzT);
            else
                pkey->asym[isym] = sym;
        }
    }
}
