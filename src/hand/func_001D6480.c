/* Allocate a new render tree block (four RENDER entries, 0x80 bytes, from the world's cleared message heap) with all
 * four entries free (kind -1). */
typedef int qword __attribute__((mode(TI)));
struct MSG { int cb; int nKind; };
struct BLOCK;
struct RENDER {
    /* 0x00 */ qword sphere;
    /* 0x10 */ float sMax;
    /* 0x14 */ long kind : 4;
    long channels : 8;
    /* 0x18 */ struct BLOCK *pblockChild;
    /* 0x1c */ int pblockNext;
};
struct BLOCK { struct RENDER arender[4]; };
void *PvAllocSwClearImpl__Fi(struct MSG *pmsg);
static inline void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSwClearImpl__Fi(pmsg); }

struct BLOCK *func_001D6480(void)
{
    struct MSG msg;
    struct BLOCK *pblock = PvAllocMsg(&msg, 0x80, 0x10);
    pblock->arender[0].kind = pblock->arender[1].kind = pblock->arender[2].kind = pblock->arender[3].kind = -1;
    return pblock;
}
