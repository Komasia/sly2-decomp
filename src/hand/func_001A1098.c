/* func_001A1098 (0x1A1098): one of the actor sub-objects' post-loads (SafeHouse sly.cpp PostLoadActorParts' list):
 * copies the static table of 7 part entries (D_002BFA30: {oid, 30.0, 0}) into the switch heap and finds each entry's
 * part record (XF) on the owner: 0x1F4C58(owner, oid, 6), the record of that tag and kind 6. */
struct PARTE { int oid; int g4; int pxf; };   /* +0x8: the part record found (kind 6) */
struct PARTS { int palo; int pad[4]; int cparte; struct PARTE *aparte; };
struct CBALIGN { int cb; int cbAlign; };
#define KIND_XF_PART 6
extern char g_aparteDefault[] __asm__("D_002BFA30");
struct PARTE *PvAllocSwCopyImpl__FiPv(struct CBALIGN *pcb, void *pvSrc);
int func_001F4C58(int palo, int oid, int kind);
void func_001A1098(struct PARTS *pparts)
{
    struct CBALIGN cb;
    int i;
    pparts->cparte = 7;
    cb.cb = 0x54;
    cb.cbAlign = 0x10;
    pparts->aparte = PvAllocSwCopyImpl__FiPv(&cb, g_aparteDefault);
    for (i = 0; i < pparts->cparte; i++) {
        struct PARTE *pparte = &pparts->aparte[i];
        pparte->pxf = func_001F4C58(pparts->palo, pparte->oid, KIND_XF_PART);
    }
}
