typedef struct { char ab[0x5408]; } BIG;
typedef struct {
    short ch;
    signed char x2;
    unsigned char x3;
    unsigned short x4;
    unsigned short iChild;
    unsigned short iSibling;
} ENT;
typedef struct { int c; ENT *ae; char ht[1]; } OBJ;
extern BIG D_003D4A60;
extern char D_002A78F8[];
int SymFromName__FP6LAYOUTPc(void *, char *);
static inline int NFind(OBJ *ph, char *pch) { return SymFromName__FP6LAYOUTPc(ph->ht, pch); }
// name: SafeHouse port (CopyGameSaveForSlot)
void CopyGameSaveForSlot__FP6LAYOUTP8GAMESAVE(OBJ *p, BIG *pbig)
{
    int n;
    int i;
    *pbig = D_003D4A60;
    n = NFind(p, D_002A78F8);
    if (n == -1)
        return;
    for (i = 0; i < p->c; i++) {
        ENT *pe = &p->ae[i];
        if (pe->ch == n)
            pbig->ab[pe->x4] = 1;
    }
}
