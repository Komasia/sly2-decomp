// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
// NOTE: 36/76 diffs. Logic right; target keeps id in v1 then copies to a2 at join, default case sets a2=0 directly, switch arms laid out as separate blocks (no beql). Tried case orders, else id=0, key copy.
typedef unsigned long u_long;
typedef struct { u_long id; u_long mask; void *func; void *data; int gp; int pad; } STRCB;
typedef struct { char pad[0x60]; STRCB *strCb; int nStrCb; } SYS;
typedef struct { char pad[0x40]; SYS *sys; } sceMpeg;
typedef struct { u_long id; u_long mask; } STRTBL;
extern STRTBL D_002C83D8[];
void *sceMpegAddStrCallback(sceMpeg *mp, unsigned int strType, int ch, void *func, void *data)
{
  SYS *p = mp->sys;
  STRCB *cbs = p->strCb;
  void *old = 0;
  u_long id = 0;
  int i;
  int gp;
  if (strType < 10) {
    int shift;
    switch (D_002C83D8[strType].mask) {
    case 0xFF00000000UL: shift = 32; break;
    case 0xFFFF000000UL: shift = 24; break;
    case 0xFFFFFFFFFFUL: shift = 0; break;
    default: goto search;
    }
    id = D_002C83D8[strType].id | ((u_long)ch << shift);
  }
search:
  for (i = 0; i < p->nStrCb; i++) {
    if (id == cbs[i].id) { old = cbs[i].func; break; }
  }
  if (i < 64) {
    cbs[i].id = id;
    cbs[i].func = func;
    cbs[i].data = data;
    cbs[i].mask = D_002C83D8[strType].mask;
    __asm__ volatile("move %0, $gp" : "=r"(gp));
    cbs[i].gp = gp;
    p->nStrCb++;
  }
  return old;
}
