/* LoadTextFromBrx: the world's texts (SW +0x4640): the languages (U8 count, each language's id; the current one's
 * index kept), then per text its S16 id and one string per language: the current language's read onto the world heap,
 * the others skipped. SafeHouse port. */
struct AREQ { int cb; int cbAlign; };
struct TEXT { int id; int pch; };   /* a text: its id, the string */
struct SW { char pad[0x4640]; int ctext; struct TEXT *atext; };
extern int D_002E1E54;   /* the language */
extern char g_heapSw[];
extern char D_003E1C20[];
int U8Read(void *pbs) asm("U8Read__18CBinaryInputStream");
int S16Read(void *pbs) asm("S16Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(struct AREQ *preq);
void func_00118380(void *pbs, int *pn, void *pv, int n);
void ReadDebugString__FP18CBinaryInputStream(void *pbs);
void func_00210BE0(void *pv);
// name: SafeHouse port (LoadTextFromBrx)
void LoadTextFromBrx__FP2SWP18CBinaryInputStream(struct SW *psw, void *pbs)
{
    struct AREQ req;
    int i;
    int iMatch = 0;
    int clang = U8Read(pbs);
    {
        int j;
        for (j = 0; j < clang; j++) {
            if (U8Read(pbs) == D_002E1E54)
                iMatch = j;
        }
    }
    i = 0;
    psw->ctext = S16Read(pbs);
    req.cbAlign = 0x10;
    req.cb = psw->ctext * sizeof(struct TEXT);
    psw->atext = (struct TEXT *)PvAllocSwImpl__Fi(&req);
    for (; i < psw->ctext; i++) {
        struct TEXT *ptext = &psw->atext[i];
        int j;
        ptext->id = S16Read(pbs);
        for (j = 0; j < clang; j++) {
            if (j == iMatch)
                func_00118380(pbs, &ptext->pch, g_heapSw, 0x2E);
            else
                ReadDebugString__FP18CBinaryInputStream(pbs);
        }
    }
    func_00210BE0(D_003E1C20);
}
